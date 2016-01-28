
#include <iostream>
#include <ctime>
#include <math.h>

#include "MUSI8903Config.h"
#include "MyProject.h"
#include "AudioFileIf.h"
using std::cout;
using std::endl;

#define pi 3.14159


// local function declarations
void    showClInfo ();
void    singen();
void    sinIIRtest();







/////////////////////////////////////////////////////////////////////////////////
// main function
int main(int argc, char* argv[])
{
    std::string             sInputFilePath,                 //!< file paths
                            sOutputFilePath;

    double               iInFileLength       = 0;        //!< length of input file

    clock_t                 time                = 0;
    
    int                     kBlockSize;

    float                   **ppfAudioData      = 0;
    
    float                   **ppfAudioDataOut   = 0;
    
    CAudioFileIf            *phAudioFile        = 0;
    
    CMyProject              *pMyProject          = 0;
   
    CAudioFileIf::FileSpec_t stFileSpec;
    
    std::fstream            hOutputFile;
    
    std::fstream            hInputFile;
    
    std::string             filterType;
    
    Error_t                 error;
    
    float                   gain;
    
    int                     delay;
    
    float                   **sine;
    
    float                   **sineOut;
    
    float                   **zeros;
    
    float                   **zerosOut;
    

    showClInfo ();

    //////////////////////////////////////////////////////////////////////////////
    // parse command line arguments
    
    if (argc < 6)
    {
        cout << "Not enough args" << endl;
        return -1;
    }
    else
    {
        sInputFilePath  = argv[1];
        sOutputFilePath = sInputFilePath + ".txt";
        filterType      = argv[2];
        gain            = std::stof (argv[3]);
        delay           = std::stof (argv[4]);
        kBlockSize      = std::stof (argv[5]);
        if (delay>kBlockSize)
        {
            cout << "Delay cannot be longer than block size" << endl;
            return -1;
        }
        
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


    //////////////////////////////////////////////////////////////////////////////
    // get audio info and print it to stdout

    
    cout << "Number of channels: " << stFileSpec.iNumChannels << endl;
    phAudioFile->getLength(iInFileLength);
    cout << "Length of file in seconds: " << iInFileLength << endl;
    cout << "Sample rate: " << stFileSpec.fSampleRateInHz << endl;
    cout << "File location: " << sInputFilePath << endl;
    
    
    //////////////////////////////////////////////////////////////////////////////
    // do testing
    cout << "Processing data is fun!" << endl << endl;
    CMyProject::create(pMyProject);
    
    
    pMyProject->init(1, 1, 10);
    
    
    //sine test
    sine = new float* [1];
    sine[0] = new float [4096];
    
    sineOut = new float* [1];
    sineOut[0] = new float [4096];
    
    int fs= 44100;
    for (int i =0; i<4096;i++){
        sine[0][i] = sin(2 *pi*2205*i/fs );
    }
    
    error = pMyProject->process(sine, sineOut, 4096, "FIR");
    
    for (int i = delay; i < 4096; i++)
    {
        
        
        if(sineOut[0][i] >0.00001 || sineOut[0][i]<-0.00001){
            cout << "sine test FIR FAILED" << endl;
            return kUnknownError;
        }
    }
    
    cout << "sine FIR test PASSED" << endl;
    
    delete [] sine[0];
    delete [] sineOut[0];
    
    pMyProject->reset();
    
    
    pMyProject->init(1, 1, 10);
    
    sine = new float* [1];
    sine[0] = new float [4096];
    
    sineOut = new float* [1];
    sineOut[0] = new float [4096];
    
    for (int i =0; i<4096;i++){
        sine[0][i] = sin(2 *pi*4410*i/fs );
    }
    
    error = pMyProject->process(sine, sineOut, 4096, "FIR");
    
    int sinSum = 0;
    int sinOutSum = 0;
    
    for (int i = 0; i < 4096; i++)
    {
        sinSum = sinSum + fabs(sine[0][i]);
        sinOutSum = sinOutSum + fabs(sineOut[0][i]);
        
        if(sinSum > sinOutSum){
            cout << "sine IIR test FAILED" << endl;
            return kUnknownError;
        }
    }
    
    cout << "sine IIR test PASSED" << endl;
    
    delete [] sine[0];
    delete [] sineOut[0];
    
    pMyProject->reset();
    //END SINE TEST
    
    //zero input test
    pMyProject->init(1, 1, 10);
    
    zeros = new float* [1];
    zeros[0] = new float [4096];
    
    zerosOut = new float* [1];
    zerosOut[0] = new float [4096];
    
    for (int i =0; i<4096;i++){
        zeros[0][i] = 0;
    }
    
    error = pMyProject->process(zeros, zerosOut, 4096, "IIR");
    
    int zerosOutSum = 0;
    
    for (int i = 0; i < 4096; i++)
    {
        zerosOutSum = zerosOutSum + fabs(zerosOut[0][i]);
        
        if(zerosOutSum > 0){
            cout << "zero input IIR test FAILED" << endl;
            return kUnknownError;
        }
    }
    
    cout << "zero input IIR test PASSED" << endl;
    
    delete [] zeros[0];
    delete [] zerosOut[0];
    
    pMyProject->reset();
    
    pMyProject->init(1, 1, 10);
    
    zeros = new float* [1];
    zeros[0] = new float [4096];
    
    zerosOut = new float* [1];
    zerosOut[0] = new float [4096];
    
    for (int i =0; i<4096;i++){
        zeros[0][i] = 0;
    }
    
    error = pMyProject->process(zeros, zerosOut, 4096, "FIR");
    
    zerosOutSum = 0;
    
    for (int i = 0; i < 4096; i++)
    {
        zerosOutSum = zerosOutSum + fabs(zerosOut[0][i]);
        
        if(zerosOutSum > 0){
            cout << "zero input FIR test FAILED" << endl;
            return kUnknownError;
        }
    }
    
    cout << "zero input FIR test PASSED" << endl;
    
    delete [] zeros[0];
    delete [] zerosOut[0];
    
    pMyProject->reset();
    // end zero input test
    
    // no gain test
    // ensure signal is unaffect if the filter is at zero gain
    pMyProject->init(1, 0, 10);
    
    sine = new float* [1];
    sine[0] = new float [4096];
    
    sineOut = new float* [1];
    sineOut[0] = new float [4096];
    
    for (int i =0; i<4096;i++){
        sine[0][i] = sin(2 *pi*4410*i/fs );
    }
    
    error = pMyProject->process(sine, sineOut, 4096, "FIR");
    
    for (int i = 0; i < 4096; i++)
    {
        if(sine[0][i] != sineOut[0][i]){
            cout << "no gain test FAILED" << endl;
            return kUnknownError;
        }
    }
    
    cout << "no gain test PASSED" << endl;
    
    delete [] sine[0];
    delete [] sineOut[0];
    
    pMyProject->reset();
    //END no Gain Test
    
    
    pMyProject->init(stFileSpec.iNumChannels, gain, delay);
    
    //allocate memory
    ppfAudioData = new float* [stFileSpec.iNumChannels];
    for (int i = 0; i < stFileSpec.iNumChannels; i++)
        ppfAudioData[i] = new float [kBlockSize];
   
    time = clock();
    
    
    ppfAudioDataOut = new float* [stFileSpec.iNumChannels];
    for (int i = 0; i < stFileSpec.iNumChannels; i++)
        ppfAudioDataOut[i] = new float [kBlockSize];
    
    //do processing
    while (!phAudioFile->isEof())
    {
        long long iNumFrames = kBlockSize;
        phAudioFile->readData(ppfAudioData, iNumFrames);
        
         error = pMyProject->process(ppfAudioData, ppfAudioDataOut, iNumFrames, filterType);
        
        if(error!=kNoError)
        {cout<< "Error: Invalid filter specification" <<endl;
            break;
        }
        
        for (int i = 0; i < iNumFrames; i++)
        {
            for (int c = 0; c < stFileSpec.iNumChannels; c++)
            {
                hOutputFile << ppfAudioDataOut[c][i] << "\t";
            }
            hOutputFile << endl;
        }
        
    }
    
    
    
    
    //////////////////////////////////////////////////////////////////////////////
    // clean-up
    
    CAudioFileIf::destroy(phAudioFile);
    hOutputFile.close();
    
    CMyProject::destroy(pMyProject);
    
    for (int i = 0; i < stFileSpec.iNumChannels; i++){
        delete [] ppfAudioData[i];
        delete [] ppfAudioDataOut[i];
    }
    delete [] ppfAudioData;
    delete [] ppfAudioDataOut;
    ppfAudioData = 0;
    ppfAudioDataOut = 0;
    return 0;
    
}

void singen(float* sine)
{
    sine = new float [4096];
    int fs= 44100;
    for (int i =0; i<=4096;i++){
        sine[i] = sin(2 *pi*2205*i/fs );
    }
    
}



void     showClInfo()
{
    cout << "GTCMT MUSI8903" << endl;
    cout << "(c) 2016 by Alexander Lerch" << endl;
    cout  << endl;

    return;
}

