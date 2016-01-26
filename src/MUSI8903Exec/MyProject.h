#if !defined(__MyProject_hdr__)
#define __MyProject_hdr__

#include "ErrorDef.h"
#include <iostream>
#include <cstring>

class CMyProject
{
public:
    /*! version number */
    enum Version_t
    {
        //kMajor,                         //!< major version number
        //kMinor,                         //!< minor version number
        //kPatch,                         //!< patch version number

        kNumVersionInts
    };

    static const int  getVersion (const Version_t eVersionIdx);
    static const char* getBuildDate ();

    static Error_t create (CMyProject*& pCKortIf);
    static Error_t destroy (CMyProject*& pCKortIf);
    
    Error_t init (int numChannels);
    Error_t reset ();
    
    virtual Error_t process (float **ppfInputBuffer, float **ppfOutputBuffer, int iNumberOfFrames, std::string filterType);
    
    float g = 0.5;
    
    float **buffer;
    
    int numChan;

protected:
    CMyProject ();
    virtual ~CMyProject ();
};

#endif // #if !defined(__MyProject_hdr__)



