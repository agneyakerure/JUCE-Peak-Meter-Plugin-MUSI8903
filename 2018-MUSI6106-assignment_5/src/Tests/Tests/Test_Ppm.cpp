#include "MUSI6106Config.h"

#ifdef WITH_TESTS
#include <cassert>
#include <algorithm>
#include <iostream>
#include "Synthesis.h"
#include "UnitTest++.h"

#include "Ppm.h"
#include "Vector.h"

using namespace std;

SUITE(Ppm)
{
    struct PpmData
    {
        PpmData() : m_fSampleRate(44200),
                    m_iNumChannels(3),
                    m_iDataLength(0),
                    m_iBlockLength(0),
                    m_AlphaAT(0),
                    m_AlphaRT(0),
                    m_epsilon(0),
                    m_currentValue(0),
                    m_tempBuff(0),
                    m_vppmMax(0)
        {
            CPpm::createInstance(m_pCPpm);
            m_pCPpm->initInstance(m_fSampleRate, m_iNumChannels);
            m_ppfInputData = new float*[m_iNumChannels];
            m_ppfOutputData = new float*[m_iNumChannels];
            m_ppfInputTmp = new float*[m_iNumChannels];
            m_pfOutputTmp  = new float[m_iNumChannels];
            
            for(int i =  0; i < m_iNumChannels; i++)
            {
                m_ppfInputData[i] = new float [m_iDataLength];
            }
        }
        
        ~PpmData()
        {
            for (int i = 0; i < m_iNumChannels; i++)
            {
                delete [] m_ppfInputData[i];
                delete [] m_ppfOutputData[i];
                delete[] m_ppfInputTmp[i];
            }
            
            delete [] m_ppfInputData;
            delete [] m_ppfOutputData;
            delete[] m_ppfInputTmp;
            delete[] m_pfOutputTmp;
            
            CPpm::destroyInstance(m_pCPpm);
        }
        
        void process()
        {
            int iNumOfPeak = 0;
            int iNumFramesRemaining = m_iDataLength;
            while (iNumFramesRemaining > 0)
            {
                int iNumFrames = std::min(iNumFramesRemaining, m_iBlockLength);
                
                for (int i = 0; i < m_iNumChannels; i++)
                {
                    m_ppfInputTmp[i] = &m_ppfInputData[i][m_iDataLength - iNumFramesRemaining];
                    
                }
                m_pCPpm->process(m_ppfInputTmp, m_pfOutputTmp, iNumFrames);
                for (int c = 0; c < m_iNumChannels; c++)
                {
                    m_ppfOutputData[c][iNumOfPeak] = m_pfOutputTmp[c];
                }
                iNumOfPeak = iNumOfPeak + 1;
                iNumFramesRemaining -= iNumFrames;
            }
        }
        
        float m_fSampleRate;
        int m_iNumChannels;
        int m_iDataLength;
        int m_iBlockLength;
        float m_AlphaAT;
        float m_AlphaRT;
        float m_epsilon;
        float m_currentValue;
        
        float *m_tempBuff;
        float *m_vppmMax;
        
        float **m_ppfInputData;
        float **m_ppfOutputData;
        float **m_ppfInputTmp;
        float *m_pfOutputTmp;
        
        CPpm *m_pCPpm;
        
    };
}

#endif //WITH_TESTS
