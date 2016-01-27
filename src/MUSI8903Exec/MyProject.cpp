
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
    
    pCMyProject->reset ();   //COMEBACK HERE AND DELETE BUFFER
    
    delete pCMyProject;
    pCMyProject = 0;

    return kNoError;

}

Error_t CMyProject::init(int numChannels, float gain) //add delay
{
    // allocate memory

    // initialize variables and buffers
    
    g = gain;
    
    numChan = numChannels;
    
    buffer = new float* [numChannels];
    for (int i = 0; i < numChannels; i++)
        buffer[i] = new float [10];
    
    

    return kNoError;
}

Error_t CMyProject::reset ()
{
    // reset buffers and variables to default values // DO SOMETHING HERE DOOFUS

    return kNoError;
}

Error_t CMyProject::process (float **ppfInputBuffer, float **ppfOutputBuffer, int iNumberOfFrames, std::string filterType)    //use delay here
{
    
    if (filterType.compare("FIR")==0) {
    
        for (int n = 0; n < iNumberOfFrames; n++)
        {
        
            for (int c = 0; c < numChan; c++)
            {
            
                ppfOutputBuffer[c][n] = ppfInputBuffer[c][n] + g * buffer[c][9];
        
                for (int i = 9; i >= 0; i--)
                {
            
                    if (i == 0)
                    {
                        buffer[c][i] = ppfInputBuffer[c][n];
                    }
                    else
                    {
                        buffer[c][i] = buffer[c][i-1];
                    }
                }
            }
    
        }
        //ppfOutputBuffer = ppfInputBuffer;

    }
    else if (filterType.compare("IIR")==0) {
            
                for (int n = 0; n < iNumberOfFrames; n++)
                {
                
                    for (int c = 0; c < numChan; c++)
                    {
                    
                        ppfOutputBuffer[c][n] = ppfInputBuffer[c][n] + g * buffer[c][9];
                    
                        for (int i = 9; i >= 0; i--)
                        {
                        
                            if (i == 0)
                            {
                                buffer[c][i] = ppfOutputBuffer[c][n];
                            }
                            else
                            {
                                buffer[c][i] = buffer[c][i-1];
                            }
                        }
                    }
                
                }
    }
    else
    {
        return kUnknownError;
    }
   
    
    return kNoError;

}




