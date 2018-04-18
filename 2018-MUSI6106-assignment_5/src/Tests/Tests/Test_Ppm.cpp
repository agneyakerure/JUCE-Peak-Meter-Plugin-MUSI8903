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
                    m_iBlockLength(512),
                    m_numBlocks(4),
                    m_AlphaAT(0),
                    m_AlphaRT(0),
                    m_epsilon(0),
                    m_currentValue(0),
                    m_tempBuff(0),
                    desierdResult(0),
                    m_vppmMax(0)
        {
            CPpm::createInstance(m_pCPpm);
            m_pCPpm->initInstance(m_fSampleRate, m_iNumChannels);
            m_ppfInputData = new float*[m_iNumChannels];
            m_ppfOutputData = new float*[m_iNumChannels];
            m_ppfInputTmp = new float*[m_iNumChannels];
            m_pfOutputTmp  = new float[m_iNumChannels];
            m_iDataLength = m_iBlockLength * m_numBlocks;
            
            for(int i =  0; i < m_iNumChannels; i++)
            {
                m_ppfInputData[i] = new float [m_iDataLength];
                CVectorFloat::setZero(m_ppfInputData[i], m_iDataLength);
                m_ppfOutputData[i] = new float [m_iDataLength];
                CVectorFloat::setZero(m_ppfOutputData[i], m_iDataLength);
                m_ppfInputTmp[i] = new float [m_iNumChannels];
                CVectorFloat::setZero(m_ppfInputData[i], m_iDataLength);
                m_pfOutputTmp[i]  = 0;
                

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
        
        
        float m_fSampleRate;
        int m_iNumChannels;
        int m_iDataLength;
        int m_iBlockLength;
        int m_numBlocks;
        
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
        float *desierdResult;
        CPpm *m_pCPpm;
        
    };
    
    TEST_FIXTURE(PpmData, InitializationTest)
    {
        Error_t err = kUnknownError;
        m_pCPpm->reset();
        m_pCPpm->initInstance(m_fSampleRate, m_iNumChannels);
        err = m_pCPpm->process(m_ppfInputTmp, m_pfOutputTmp, 0);
        CHECK (err == kNoError);
    }
    
    
    TEST_FIXTURE(PpmData, ResetTest)
    {
        Error_t err = kUnknownError;
        m_pCPpm->reset();
        err = m_pCPpm->process(m_ppfInputTmp, m_pfOutputTmp, 0);
        CHECK (err == kNoError);
    }
    
    TEST_FIXTURE(PpmData, ZeroInputSignal)
    {
        desierdResult = new float[m_iNumChannels];
        for (int i = 0; i < m_iNumChannels; i++)
        {
            m_pCPpm->reset();
            m_pCPpm->initInstance(m_fSampleRate, m_iNumChannels);
            desierdResult[i] = 0;
        }
        
        
        m_pCPpm->process(m_ppfInputData, m_pfOutputTmp, m_iDataLength);
        CHECK_ARRAY_CLOSE(desierdResult, m_pfOutputTmp, m_iNumChannels, 1e-2);

    }
    
    TEST_FIXTURE(PpmData, PpmDCInput)
    {
        m_pCPpm->reset();
        m_pCPpm->initInstance(m_fSampleRate, m_iNumChannels);
        m_pCPpm->setAlphaAT(0.1);
        desierdResult = new float[m_iNumChannels];

        for (int i = 0; i < m_iNumChannels; i++)
        {
            CSynthesis::generateDc(m_ppfInputData[i], m_iDataLength, 1);
            desierdResult[i] = 1;
        }
        
        m_pCPpm->process(m_ppfInputData, m_pfOutputTmp, m_iDataLength);
        CHECK_ARRAY_CLOSE(desierdResult, m_pfOutputTmp, m_iNumChannels, 1e-3);
    }
    
    
    
   

}

#endif //WITH_TESTS
