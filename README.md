# MUSIC-8903-2016
Repo for the class Audio Software Engineering Spring 2016

Greg Hendler Keshav Venkat
MUSI 8903
Hwk 1

1.
In processing, a user can toggle between FIR and IIR filters, the gain (g) of the filter response, the delay of the filter, and the block size. Max delay is determined by the block size. The maximum delay is equivalent to the block size. All of these parameters can be set in the command line. Our interface accommodates all channel configurations and sample rates. The user accesses both types of filter by typing either ‘IIR’ or ‘FIR’ as a command line argument. Our process function is not in place. We thought it would be safest to keep input and output data separate so as to not run the risk of overwriting data.

4. Describe input arguments and output to command line functionality
The input arguments are as follows: wav file, filter type string, feedback gain, delay, and block size.

The outputs include a txt file with the results of the filtering organized by channel, and information about input audio file. This includes: number of channels, file length in seconds, sample rate, file location and a positive message of encouragement. 

If an occurs, eg. user specifies incorrect filter type, an error message will appear on the console.

5. 
When using ‘2notes_test.wav’ we recorded a maximum error between matlab and C++ code FIR implementations  of 5.0000E-07.

When using ‘2notes_test.wav’ we recorded a maximum error between matlab and C++ code IIR implementations  of 5.0831E-07.

When using ‘ABBA.wav’ we recorded a maximum error between matlab and C++ code FIR implementations  of 5.0000E-06 for channel 1, 5.0000E-06 for channel 2.

When using ‘ABBA.wav’ we recorded a maximum error between matlab and C++ code IIR implementations  of 5.0751E-06 for channel 1, 5.0744E-06 for channel 2.

6. 
Console outputs will show whether or not test cases has passed correctly or not. These can be commented in or out as the user wishes.
We implemented the following tests:
1.	zero output if input frequency matches feedforward (FIR)                                         
2.	magnitude increase/decrease if input frequency matches feedback (IIR)                                                                           
4.	zero input signal (FIR & IIR)                                                                                          
5.	additional test to verify correct functionality
⁃	This test verifies that when gain is 0 the output is identical to the input 


