#include "itkGPUImage.h"
#include "itkImageFileReader.h"
#include "itkGPUDiscreteGaussianImageFilter.h"

int test(std::string inputFilename)
{

  typedef itk::GPUImage< unsigned char, 2 > UnsignedCharImageType;
  typedef itk::GPUImage< float, 2 >         FloatImageType;
  typedef itk::ImageFileReader< UnsignedCharImageType >  readerType;

  typedef itk::GPUDiscreteGaussianImageFilter<
    UnsignedCharImageType, FloatImageType >  filterType;

  // Create and setup a reader
  readerType::Pointer reader = readerType::New();
  reader->SetFileName( inputFilename.c_str() );
  UnsignedCharImageType::Pointer input = reader->GetOutput();
  reader->Update();
  input->DisconnectPipeline();

 // std::cout<<"\n--\n In Size: "<<input->GetLargestPossibleRegion().GetSize()<<std::endl;

  // Create and setup a Gaussian filter
  filterType::Pointer gaussianFilter = filterType::New();

  gaussianFilter->SetInput( input );
  gaussianFilter->SetVariance(4.0);
  gaussianFilter->Update();

  FloatImageType::Pointer output(FloatImageType::New());
  output=gaussianFilter->GetOutput();

 // std::cout<<"Out Size: "<<output->GetLargestPossibleRegion().GetSize()<<std::endl;
  return 1;
}
int main(int argc, char * argv[])
{
    int done=0;

    // Verify command line arguments
    if( argc < 3 )
    {
        std::cerr << "Usage: " << std::endl;
        std::cerr << argv[0] << " inputImageFile iterations" << std::endl;
        return -1;
    }
    std::string inputFilename = argv[1];
    int iter = atoi(argv[2]);

    for(int i=0 ; i<iter; ++i)
    {
        done += test(inputFilename);
    }
    std::cout<<"Total iterations: "<<done<<std::endl;

    return done;
}
