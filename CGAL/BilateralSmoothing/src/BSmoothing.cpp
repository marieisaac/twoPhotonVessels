#include <CGAL/Simple_cartesian.h>
#include <CGAL/property_map.h>
#include <CGAL/IO/read_xyz_points.h>
#include <CGAL/IO/write_xyz_points.h>
#include <CGAL/bilateral_smooth_point_set.h>
#include <CGAL/tags.h>
#include <utility> // defines std::pair
#include <fstream>
// Types
typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_3 Point;
typedef Kernel::Vector_3 Vector;
// Point with normal vector stored in a std::pair.
typedef std::pair<Point, Vector> PointVectorPair;
int main(int argc, char*argv[])
{
// argv[0]= the .xyz file with point cloud information to be inputted
//argv[1]= the simplified .xyz file with point cloud information to be outputted
//argv[2]= the control sharpness of the result
// argv[3]= the number of times the projection is applied
int sharp; 
int iterNum;
if (argc==1){
	    	const char* input_filename  = "/home/highschoolintern/Desktop/XYZFileWriter/Vertices.xyz";
	  const char* output_filename = "/home/highschoolintern/Desktop/XYZFileWriter/VerticesOutRem.xyz";
		  sharp= 20 ;
		interNum=2 ;
	    }else {
	    	const char*  input_filename = argv[0];
	    		  const char* output_filename = argv[1];
	    	iterNum= argv[3];
		sharp = argv[2];
	    }
  
// Reads a .xyz point set file in points[] * with normals *.
  std::vector<PointVectorPair> points;
  std::ifstream stream(input_filename);
  std::cout<< "reading file.......";
  if (!stream ||
      !CGAL::read_xyz_points_and_normals(stream,
                     std::back_inserter(points),
                     CGAL::First_of_pair_property_map<PointVectorPair>(),
                     CGAL::Second_of_pair_property_map<PointVectorPair>()))
  {
     std::cerr << "Error: cannot read file " << input_filename << std::endl;
     return EXIT_FAILURE;
  }else {
	  std::cout<< "complete" << "\n" ;
  }

  // Algorithm parameters
  int k = 75;                 // size of neighborhood. The bigger, the smoother the result will be.
                               // This value should bigger than 1.
  double sharpness_angle = sharp; // control sharpness of the result.
                               // The bigger the smoother the result will be
  int iter_number = iterNum;         // number of times the projection is applied
  
Std::cout << "Smoothing........";
  for (int i = 0; i < iter_number; ++i)
  {
    /* double error = */
    CGAL::bilateral_smooth_point_set <CGAL::Parallel_tag>(
          points.begin(), 
          points.end(),
          CGAL::First_of_pair_property_map<PointVectorPair>(),
          CGAL::Second_of_pair_property_map<PointVectorPair>(),
          k,
          sharpness_angle);
  }
  Std::cout << "complete \n";
  
  std::ofstream out(output_filename);   
 std::cout << "Creating and Saving file......." ;
  if (!out ||
      !CGAL::write_xyz_points_and_normals(
      out, points.begin(), points.end(),
      CGAL::First_of_pair_property_map<PointVectorPair>(),
      CGAL::Second_of_pair_property_map<PointVectorPair>()))

  {
	  std::cout<<"something went wrong? \n";
	  return EXIT_FAILURE;
  }
  std::cout << "complete \n";
  return EXIT_SUCCESS;
}
