#include "stdafx.h"
#include "Polygon_Reader.h"


void Polygon_Reader::Build_Polygon_Index(Polygon_File& PF)
{
	string line;
	ifstream ifs(this->poly_file_name,ifstream::in);
	if(ifs.good())
	{
		while (!ifs.eof())
		{
			getline(ifs,line);
			if (line.compare("") != 0) PF.Add(Parse_Polygon(line));
		}
		ifs.close();
	}
	else //cout <<  << poly_file_name << " !"<< endl;
		throw std::runtime_error("ERROR: can't open polygon file: " + poly_file_name);
  }

void Polygon_Reader::split(const std::string& s, char delim, std::vector<std::string>& elems)
{
	std::string ele;
	std::stringstream stream(s);
	while(std::getline(stream,ele, delim))
		elems.push_back(ele);
}

Polygon* Polygon_Reader::Parse_Polygon(string line)
{
	size_t start, end, pos;
	std::string head_str, gml_str;
	std::vector<std::string> temp_str_array;
	std::vector<std::string> coord_array;

	pos = line.find_first_of("<");
	head_str = line.substr(0, pos);
	split(head_str,':',temp_str_array);
	gml_str = line.substr(pos);

	start = gml_str.find_first_of("<");
	end= gml_str.find_first_of(">");
	std::string tag = gml_str.substr(start, end - start);
	std::string tag_name = "";

	start = tag.find_first_of("<"); 
	tag_name = tag_name + tag.substr(start, tag.find_first_of(" ") - start);
	tag_name = tag_name + ">";
	tag_name.insert(1, "/");

	start = end + 1;
	end = gml_str.find(tag_name);
	gml_str = gml_str.substr(start, end - start);    //get rid of polygon tag

	start = gml_str.find_first_of("<");
	end = gml_str.find_first_of(">");
	tag = gml_str.substr(start, end - start + 1);

	tag_name = tag;
	tag_name.insert(1, "/");

	//remove the tags of the outerBoundary
	start = end + 1;
	end = gml_str.find(tag_name);
	std::string tag_value = gml_str.substr(start, end - start);
	gml_str = gml_str.substr(gml_str.find(tag_name) + tag_name.length());   //rest of the string after remove the outer Boundary part

	start = tag_value.find("<gml:coordinates");
	end = tag_value.find("</gml:coordinates");
	std::string tmp_str = tag_value.substr(start, end - start);
	std::string Coord = tmp_str.substr(tmp_str.find_first_of(">") + 1);
		
	split(Coord, ' ', coord_array);
	std::vector<std::string> xy_array;
	LinearRing* lr_OB = new LinearRing();
	for (std::string xy : coord_array){
		split(xy, ',', xy_array);
		lr_OB->Add_Point(new Point(stod(xy_array[0]), stod(xy_array[1])));
		xy_array.clear();
	}

	OuterBoundary* OB = new OuterBoundary(lr_OB);
	Polygon* poly = new Polygon(stoi(temp_str_array[1]), stoi(temp_str_array[2]), OB);

	xy_array.clear();
	coord_array.clear();

	while (gml_str != "")
	{
		start = gml_str.find_first_of("<");
		end = gml_str.find_first_of(">");
		tag = gml_str.substr(start, end - start + 1);
		if (tag.find("innerBoundaryIs")!= 0){
			tag_name = tag;
			tag_name.insert(1, "/");

			start = end + 1;
			end = gml_str.find(tag_name);
			std::string tag_value = gml_str.substr(start, end - start);
			gml_str = gml_str.substr(gml_str.find(tag_name) + tag_name.length());
			
			start = tag_value.find("<gml:coordinates");
			end = tag_value.find("</gml:coordinates");
			tmp_str = tag_value.substr(start, end - start);
			Coord = tmp_str.substr(tmp_str.find_first_of(">") + 1);
			split(Coord, ' ', coord_array);

			LinearRing* lr_IB = new LinearRing();
			for (std::string xy: coord_array){
				split(xy, ',', xy_array);
				lr_IB->Add_Point(new Point(stod(xy_array[0]), stod(xy_array[1])));
				xy_array.clear();
			}
			poly->Add_Inner_Boundary(new InnerBoundary(lr_IB));
			xy_array.clear();
	        coord_array.clear();
		}
	}

	return poly;
}


Polygon_Reader::~Polygon_Reader(void)
{
}
