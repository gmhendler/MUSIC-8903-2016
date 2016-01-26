
// standard headers

// project headers
#include "ErrorDef.h"

#include "MyProject.h"

static const char*  kCMyProjectBuildDate             = __DATE__;


CMyProject::CMyProject ()
{
    // this never hurts
    this->reset ();
}


CMyProject::~CMyProject ()
{
    this->reset ();
}

const int  CMyProject::getVersion (const Version_t eVersionIdx)
{
    int iVersion = 0;

    /*switch (eVersionIdx)
    {
    case kMajor:
        iVersion    = MyProject_VERSION_MAJOR; 
        break;
    case kMinor:
        iVersion    = MyProject_VERSION_MINOR; 
        break;
    case kPatch:
        iVersion    = MyProject_VERSION_PATCH; 
        break;
    case kNumVersionInts:
        iVersion    = -1;
        break;
    }*/

    return iVersion;
}
const char*  CMyProject::getBuildDate ()
{
    return kCMyProjectBuildDate;
}

Error_t CMyProject::create (CMyProject*& pCMyProject)
{
    pCMyProject = new CMyProject ();

    if (!pCMyProject)
        return kUnknownError;


    return kNoError;
}

Error_t CMyProject::destroy (CMyProject*& pCMyProject)
{
    if (!pCMyProject)
        return kUnknownError;
    
    pCMyProject->reset ();
    
    delete pCMyProject;
    pCMyProject = 0;

    return kNoError;

}

Error_t CMyProject::init(int numChannels)
{
    // allocate memory

    // initialize variables and buffers
    
    buffer = new float* [numChannels];
    for (int i = 0; i < numChannels; i++)
        buffer[i] = new float [10];
    
    

    return kNoError;
}

Error_t CMyProject::reset ()
{
    // reset buffers and variables to default values

    return kNoError;
}

 Error_t CMyProject::process (float **ppfInputBuffer, float **ppfOutputBuffer, int iNumberOfFrames)
{

    /*
    Delayline=zeros(10,1);% memory allocation for length 10
        for n=1:length(x);
    y(n)=x(n)+g*Delayline(10);
    Delayline=[x(n);Delayline(1:10-1)];
    end;
     */
    
    ppfOutputBuffer = ppfInputBuffer;
    
    return kNoError;

}




