/*
// Geofence.cpp : Defines the entry point for the console application.
*/

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <time.h>
#include <iomanip>
#include <thread>
#include "Point_Factory.h"
#include "Output_unord.h"
#include "Polygon_File.h"
#include "Text_File_Reader.h"
#include "Polygon_Reader.h"
#include "Point_Factory.h"
#include "Point_Processor.h"
#include "Logger.h"

using namespace std;

int main(int argc, char* argv[])
{
	//auto t1 = chrono::high_resolution_clock::now();

	if (argc < 5)
	{
		std::cout << "Not enough parameter !!";
		return 0;
	}

	string pred;
	string dist;
	string pt_file_name;
	string poly_file_name;
	string out_file_name;
	string nthd;
	string out_op;

	int n_thread;
	const string log_file_name = "geofence.log";

	if (argc == 5)
	{
		pred.assign(argv[1]);
		dist = "";
		pt_file_name.assign(argv[2]);
		poly_file_name.assign(argv[3]);
		out_file_name.assign(argv[4]);
		
		//get the number of cores of the CPU
		n_thread = std::thread::hardware_concurrency();
	}

	if (argc == 6)
	{
		pred.assign(argv[1]);
		dist.assign(argv[2]);
		pt_file_name.assign(argv[3]);
		poly_file_name.assign(argv[4]);
		out_file_name.assign(argv[5]);

		n_thread = std::thread::hardware_concurrency();
	}

	Predicate* p = new Predicate(pred,dist);
	//validate predicate
	if (! p->Validate_Argv()) 
	{
		std::cout << "Illigal predicate string, please double Check !!";
		delete p;
		p = NULL;
		return 0;
	}

	try
	{
		//create utilities
		Output_unord out_set(out_file_name);
		Polygon_File PF(p);
		Polygon_Reader poly_gr(poly_file_name);
		Point_Factory pt_f;
		Text_File_Reader txt_reader(pt_file_name);

		//build up index
		poly_gr.Build_Polygon_Index(PF);

		txt_reader.Open_file();

		//multi-thread part
		vector<std::thread> threads;

		Point_Processor pt_proc(out_set,txt_reader,pt_f,PF);

		for(int i = 0; i < n_thread; ++i){
			threads.push_back(thread(pt_proc));
		}

		//wait until finish
		for(int i = 0; i < n_thread; ++i){
			threads[i].join();
		}

		auto t3 = chrono::high_resolution_clock::now();

		txt_reader.Close_file();
		out_set.Write_to_File();

	/*
		//write log
		ostringstream contents;
		contents << pt_file_name << " "<<poly_file_name<< " "<< pred << " "<<dist<<endl; //<< " Result: " <<out_set.Get_Rec_Num() << " records. \n";		 
		contents<< "Time elapsed: " << chrono::duration_cast<chrono::milliseconds>(t3-t1).count() << " milliseconds\n";

		Logger log(log_file_name);
		log.Write_Out(contents.str());

		//write to console
		std::cout<<contents.str(); 

	*/
		std::cout << "Done !";

		return 0;
	}
	catch (runtime_error &re)
	{
		std::cout<< re.what();
		return 0;
	}
}


