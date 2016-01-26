
#include <iostream>
#include <ctime>

#include "MUSI8903Config.h"
#include "MyProject.h"
#include "AudioFileIf.h"

using std::cout;
using std::endl;

// local function declarations
void    showClInfo ();

/////////////////////////////////////////////////////////////////////////////////
// main function
int main(int argc, char* argv[])
{
    std::string             sInputFilePath,                 //!< file paths
                            sOutputFilePath;

    long long               iInFileLength       = 0;        //!< length of input file

    clock_t                 time                = 0;
    
    static const int        kBlockSize          = 1024;

    float                   **ppfAudioData      = 0;
    
    CAudioFileIf            *phAudioFile        = 0;
    
    CMyProject              *pMyProject          = 0;
   
    CAudioFileIf::FileSpec_t stFileSpec;
    
    std::fstream            hOutputFile;
    
    std::fstream            hInputFile;
    
    std::string             filterType;
    
    Error_t                     error;

    showClInfo ();

    //////////////////////////////////////////////////////////////////////////////
    // parse command line arguments
    
    if (argc < 3)
    {
        return -1;
    }
    else
    {
        sInputFilePath  = argv[1];
        sOutputFilePath = sInputFilePath + ".txt";
        filterType      = argv[2];
        
    }
    
    //////////////////////////////////////////////////////////////////////////////
    // open the input wave file
    
    CAudioFileIf::create(phAudioFile);
    phAudioFile->openFile(sInputFilePath, CAudioFileIf::kFileRead);
    if (!phAudioFile->isOpen())
    {
        cout << "Wave file open error!";
        return -1;
    }
    
    phAudioFile->getFileSpec(stFileSpec);
    
    //////////////////////////////////////////////////////////////////////////////
    // write to text files
    
    hOutputFile.open (sOutputFilePath.c_str(), std::ios::out);
    if (!hOutputFile.is_open())
    {
        cout << "Text file open error!";
        return -1;
    }
/*
    hOutputFile.open (sOutputFilePath.c_str(), std::ios::out);
    if (!hOutputFile.is_open())
    {
        cout << "Text file open error!";
        return -1;
    }*/

    //////////////////////////////////////////////////////////////////////////////
    // get audio info and print it to stdout

    
    cout << "Number of channels: " << stFileSpec.iNumChannels << endl;
    cout << "Length of file in seconds: " << phAudioFile->getLength(iInFileLength) << endl;
    cout << "Sample rate: " << stFileSpec.fSampleRateInHz << endl;
    cout << "File location: " << sInputFilePath << endl;
    
    
    //////////////////////////////////////////////////////////////////////////////
    // do processing
    cout << "Processing data is fun!" << endl << endl;
    CMyProject::create(pMyProject);
    pMyProject->init(stFileSpec.iNumChannels);
    
    //allocate memory
    ppfAudioData = new float* [stFileSpec.iNumChannels];
    for (int i = 0; i < stFileSpec.iNumChannels; i++)
        ppfAudioData[i] = new float [kBlockSize];
    time = clock();
    
    while (!phAudioFile->isEof())
    {
        long long iNumFrames = kBlockSize;
        phAudioFile->readData(ppfAudioData, iNumFrames);
        
         error = pMyProject->process(ppfAudioData, ppfAudioData, iNumFrames, filterType);
        
        if(error!=kNoError)
        {cout<< "Error: Invalid filter specification" <<endl;
            break;
        }
        
        for (int i = 0; i < iNumFrames; i++)
        {
            for (int c = 0; c < stFileSpec.iNumChannels; c++)
            {
                hOutputFile << ppfAudioData[c][i] << "\t";
            }
            hOutputFile << endl;
        }
        
    }
    
    
    
    
    //////////////////////////////////////////////////////////////////////////////
    // clean-up

    CAudioFileIf::destroy(phAudioFile);
    hOutputFile.close();
    
    for (int i = 0; i < stFileSpec.iNumChannels; i++)
        delete [] ppfAudioData[i];
    delete [] ppfAudioData;
    ppfAudioData = 0;
    
    
    
    return 0;
    
}


void     showClInfo()
{
    cout << "GTCMT MUSI8903" << endl;
    cout << "(c) 2016 by Alexander Lerch" << endl;
    cout  << endl;

    return;
}

