/*-----------------------------------------------------------------------

  File        : PGlml.cpp

  Description : Particle parameters Generator of the Laboratory of Mechanic
s in Lille (LML)

  Author      : Sebastien COUDERT
  
  --------------------------------------------------------------------*/

/*Additional documentation for the generation of the reference page (using doxyg
en)*/
/** \mainpage
 *
 *  index:
 *  \li \ref sectionCommandLine
 *  \li \ref sectionPGlmlDocumentation
 *  \li \ref sectionDoxygenSyntax
 *
 *  \section sectionCommandLine command line options
 *  \verbinclude "PGlml.help.output"
 *
 *  \section sectionPGlmlDocumentation documentation outline
 *  This is the reference documentation of <a href="http://www.meol.cnrs.fr/">PI
Vlml</a>, from the <a href="http://www.univ-lille1.fr/lml/">LML</a>.\n\n
 *  PIVlml is a PIV image processing software. The program begins in the main fu
nction in the <a href="_p_i_vlml_8cpp.html#a1">PIVlml.cpp</a> source file.\n\n
 *  This documentation has been automatically generated from the PIVlml sources,
 
 *  using the tool <a href="http://www.doxygen.org">doxygen</a>. It should be re
aded as HTML, LaTex and man page.\n
 *  It contains both
 *  \li a detailed description of all classes and functions
 *  \li a user guide (cf. \ref pages.html "related pages")
 *
 *  that as been documented in the sources.
 *
 *  \par Additional needed libraries:
 *
 *  \li <a href="http://cimg.sourceforge.net">the CImg Library</a> using <a href
="http://www.imagemagick.org/">ImageMagick</a> for a few image format
 *
 *
 *  \section sectionDoxygenSyntax make documentation using Doxygen syntax
 *  Each function in the source code should be commented using \b doxygen \b syn
tax in the same file.
 *  The documentation need to be written before the function.
 *  The basic syntax is presented in this part.
 *  \verbinclude "doxygen.example1.txt"
 *
 *  Two kind of comments are needed for \b declaration and \b explanation \b par
ts of the function:
 *  Standart documentation should the following (\b sample of code documentation
):
 *  \verbinclude "doxygen.example2.txt"
 *
 *  In both declaration and explanation part, \b writting and \b highlithing syn
tax can be the following:\n\n
 *  \li \c \\code to get\n
 *
 *  \li \c \\n    a new line
 *  \li \c \\li   a list (dot list)
 *
 *  \li \c \\b    bold style
 *  \li \c \\c    code style
 *  \li \c \\e    enhanced style (italic)
 *
 *  For making \b shortcut please use:\n
 *  \li \c \\see to make a shortcut to a related function or variable
 *  \li \c \\link to make a shortcut to a file or a function
 *  \note this keyword needs to be closed using \c \\end*
 *
 *  \li \c \\todo to add a thing to do in the list of <a href="./todo.html">oDo</
a> for the whole program
 *
 *  In explanation part, \b paragraph style can be the following:\n
 *  \li \c \\code for an example of the function use
 *  \li \c \\note to add a few notes
 *  \li \c \\attention for SOMETHING NOT FULLY DEFINED YET
 *  \li \c \\warning to give a few warning on the function
 *  \note these keywords need to be closed using \c \\end*
 *
 *  \verbinclude "doxygen.example3.txt"
 *
 *  Many other keywords are defined, so please read the documentation of <a href
="http://www.doxygen.org/commands.html">doxygen</a>.
 *
**/

#include<iostream>

//debug display (0- quiet, 1- only final image, 2- image step by step)
//#define cimg_debug 0
//#define cimg_debug 1
#define cimg_debug 2
#include "../CImg/CImg.h"

using namespace cimg_library;
using namespace std;

//The lines below are necessary when using a non-standard compiler as visualcpp6.
#ifdef cimg_use_visualcpp6
#define std
#endif
#ifdef min
#undef min
#undef max
#endif
//end visualcpp6

//create random position and size particles
/* create particle parameters with random generator:
 * gaussian particle parameters: position x and y, sigma and maximum
 * (random level for parameters)
 * \param[out] particles: all particle parameters
 * \param[in] n: number of particles to create
 * \param[in] min_x: minimum of the particle position range along x axis
 * \param[in] max_x: maximum of the particle position range along x axis
 * \param[in] min_y: minimum of the particle position range along y axis
 * \param[in] max_y: maximum of the particle position range along y axis
 * \param[in] min_s: minimum of the particle size range
 * \param[in] max_s: maximum of the particle size range
 * \param[in] min_m: minimum of the particle gray level range
 * \param[in] max_m: maximum of the particle gray level range
 * \param[in] max_m: maximum of the particle gray level range
 * \param[in|optional] mask: mask for particle area (i.e. 0 no particle, 1 available area for particles)
**/
template<typename T> int create_gaussian_random_parameters(CImg<T> &particles/*gaussian particles: position x,y; size; level*/,
  /*number*/int n,
  /*positions*/T min_x,T max_x,T min_y,T max_y,
  /*sigma*/T min_s,T max_s,
  /*maximum*/T min_m,T max_m,
  /*mask for particle area*/CImg<float> &mask
  )
{
#define POS_X 0
#define POS_Y 1
#define SIGMA 2
#define LEVEL 3
  CImg<float> coord_x(n),coord_y(n),psigma(n),color(n);
//create random particle parameters: 2D gaussian function
  ///2D position of the maximum (i.e. particle position)
  coord_x.rand(min_x,max_x);coord_y.rand(min_y,max_y);
  if(!mask.is_empty())
  {
    cimg_forX(coord_x,i)
    {
      int x=(int)coord_x(i);
      int y=(int)coord_y(i);
      if(mask(x,y)==0)
      {
        float xf,yf;
        CImg<float> r(1,1,1,1);
//int d=0;
        while(mask(x,y)==0) {r.rand(min_x,max_x);xf=r(0);x=(int)r(0);r.rand(min_y,max_y);yf=r(0);y=(int)r(0);}
//d++;cerr<<d<<" (x,y)=("<<x<<","<<y<<")=("<<xf<<","<<yf<<")"<<endl;}
        coord_x(i)=xf;
        coord_y(i)=yf;
      }
    }
  }
  ///sigma of the gaussian curve (i.e. particle size)
  psigma.rand(min_s,max_s);
  ///maximum level (i.e. particle brightness)
  color.rand(min_m,max_m);
  particles.assign(n,1,1,4);
  cimg_forX(particles,i)
  {
    particles(i,0,0,POS_X)=coord_x(i);
    particles(i,0,0,POS_Y)=coord_y(i);
    particles(i,0,0,SIGMA)=psigma(i);
    particles(i,0,0,LEVEL)=color(i);
  }
  return 0;
}//create_gaussian_random_parameters

//! draw particle position within the image
/* create single pixel particles within the image to show position only.
 * \param[in/out] image: particle image
 * \param[in] particles: all particle parameters
**/
template<typename imageT, typename T> int draw_particle_position(CImg<imageT> &image, CImg<T> &particles,int radius=3)
{
#define POS_X 0
#define POS_Y 1
  imageT color=cimg::type<imageT>::max();
//set background to 0
  image.fill(0);
//draw particles on the image
  cimg_forX(particles,i)
  {
    int x=(int)particles(i,0,0,POS_X);
    int y=(int)particles(i,0,0,POS_Y);
    if( (x>-radius) && x<image.dimx()+radius && (y>-radius) && y<image.dimy()+radius ) image.draw_circle(x,y,radius,&color);
  }
  return 0;
}//draw_particle_position

int main(int argc,char **argv)
{
  // Usage of the program displayed at the command line
  cimg_usage("Particle parameter Generator of LML");
  const bool help = cimg_option("-h",false,"Display Help");
//tests
  const bool test_mask = cimg_option("--test-mask",false,"Run and show mask test");
  const bool test_text = cimg_option("--test-text",false,"Run and show text mask test (use also --text)");
  const char* option_text= cimg_option("--text",")","Render this text as available area for the particles");
//particles
  ///particle number
  int nbParticles= cimg_option("-n",1234,"number of particles");
  ///particle size
  float sigma_min= cimg_option("-s",1.0,"minimum value of sigma of gaussian function (i.e. minimum size)");
  float sigma_max= cimg_option("-S",2.0,"maximum value of sigma of gaussian function (i.e. maximum size)");
  ///particle grey level dynamics
  float brightness_min = cimg_option("-b",200,"minimum value of amplitude of the gaussian function (i.e. minimum brightness)");
  float brightness_max = cimg_option("-B",255,"maximum value of amplitude of the gaussian function (i.e. maximum brightness)");
  ///particle file name (output)
  const char* filename= cimg_option("-o","particle_parameters.cimg","file name to output all parameters of the particles");
//volume
  ///volume size
  float width_min = cimg_option("-x",-10.5,"width  minimum value of the particle volume");
  float width_max = cimg_option("-X",521.5,"width  maximum value of the particle volume");
  float height_min= cimg_option("-y",-10.5,"height minimum value of the particle volume");
  float height_max= cimg_option("-Y",521.5,"height maximum value of the particle volume");
  ///mask image file name (optional input)
  const char* option_mask_filename= cimg_option("-M",(char*)NULL,"image file name of the particle mask (0 no particle, 1 particle area)");
//image
  ///position image file name (optional output)
  const bool option_image=cimg_option("-O",false,"Display position image");
  const char* option_image_filename=cimg_option("-P","false","file name to output positions in an image (e.g. -P positions.png)");
  const bool option_image_file=cimg::strcmp(option_image_filename,"false");

  if(help) return 0;
  
//create particle parameters
///create parameter array
  CImg<float> particles;
///create mask (optional)
  CImg<float> mask;
  unsigned int size_x,size_y;
  float zoom,color,background;
////mask test assign
  if(test_mask||test_text)
  {
    size_x=(unsigned int)(width_max+width_min+1);size_y=(unsigned int)(height_max+height_min+1);
    zoom=400,color=1,background=0;
    mask.assign((int)(size_x*100/zoom),(int)(size_y*100/zoom),1,1);
  }
////default mask test
  if(test_mask)
  {
//    mask.draw_rectangle(size_x/3,size_y/3,2*size_x/3,2*size_y/3,&color);
    mask.draw_text(10,0,"PIV",&color,&background,1,100)
    .draw_text(40,70,"lml",&color,&background,1,100);
  }
////user text mask test
  if(test_text)
  {
    mask.draw_text(10,0,option_text,&color,&background,1,100);
  }
////mask test finalize
  if(test_mask||test_text)
  {
    mask.resize((int)-zoom,(int)-zoom);
  }
////user mask (from image file)
  if(option_mask_filename!=NULL) mask.load(option_mask_filename);
#if cimg_debug>1
  if(mask.is_empty()) cerr<<"Information: no particle mask used"<<endl; else mask.display("particle mask PGlml");
#endif
///create parameters
  create_gaussian_random_parameters(particles,nbParticles,
    width_min,width_max,height_min,height_max,
    sigma_min,sigma_max,
    brightness_min,brightness_max,
    mask);
///save parameters
  particles.save(filename);
#if cimg_debug>1
    particles.display("particle parameters PGlml");
#endif

//create particle position image (optional)
  if(option_image||option_image_file)
  {
  //create image
    unsigned int size_x=(unsigned int)(width_max+width_min+1),size_y=(unsigned int)(height_max+height_min+1);
    CImg<unsigned char> image(size_x,size_y,1);
  //draw particles within the image
    draw_particle_position(image,particles);
  //save
  ///08bit
    if(option_image_file) image.save(option_image_filename);
#if cimg_debug>0
    if(option_image) image.display("particle position only PGlml");
#endif
  }
 return 0;
}//main


