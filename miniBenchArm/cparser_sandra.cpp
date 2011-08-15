#include "cparser_sandra.h"

cParser_Sandra::cParser_Sandra()
{
   cerr << "cParser_Sandra created." << endl;
}

cParser_Sandra::~cParser_Sandra()
{
   cerr << "cParser_Sandra destroyed." << endl;
}

QString cParser_Sandra::ParseInputString()
{
   fqstrParsedResult = "";
   ExtractProcessorArithmetic();
   ExtractProcessorMultiMedia();
   ExtractPowerManagement();
   ExtractCryptography();
   ExtractNetArithmetic();
   ExtractNetMultiMedia();
   ExtractVideoRendering();
   ExtractMemoryBandwidth();
   ExtractMemoryLatency();
   ExtractCacheAndMemory();
   ExtractFileSystems();
   return fqstrParsedResult;
}

bool cParser_Sandra::SkipToTestResults( const QString TEST_LABEL )
{
   const QString BENCHMARK_RESULTS_LABEL = "< Benchmark Results >";
   bool lboolLineFound = true;
   // initialize text stream:
   fInputTextStream.setString( &fqstrInputString );
   QString lqstrReadLine = fInputTextStream.readLine();

   // skip down to the test label:
   do
   {
      lqstrReadLine = fInputTextStream.readLine();
      if( fInputTextStream.atEnd() )
      {
         lboolLineFound = false;
         break;
      }
   } while( not lqstrReadLine.contains( TEST_LABEL ) );

   if( lboolLineFound )
   {// skip down to Benchmark Results:
      do
      {
         lqstrReadLine = fInputTextStream.readLine();
         if( fInputTextStream.atEnd() || lqstrReadLine.contains( "<<<" ) ) // at end of file or at start of next test
         {
            lboolLineFound = false;
            break;
         }
      } while( not lqstrReadLine.contains( BENCHMARK_RESULTS_LABEL ) );
   }
   return lboolLineFound;
}

// the following routine pulls in the result line and parses it:
void cParser_Sandra::ParseResult(QString aqstrResultLabel,
                                 bool aboolLineFound)
{
   QString lqstrStringSplitArray;
   QString lqstrReadLine;
   QString lqstrResult;

   if( aboolLineFound )
   {
      lqstrReadLine = fInputTextStream.readLine();
      if( fInputTextStream.atEnd() )
      {
         lqstrResult = "0";
      } else
      {
         QStringList lqslSplit = lqstrReadLine.split( SANDRA_RESULT_DELIMITER );
         lqstrResult = lqslSplit.at(1); // 0-based index; get result
      }
   } else
   {
      lqstrResult = "0";
   }
   if( fboolLabelResults )
   {
      lqstrResult = aqstrResultLabel
                    + OUTPUT_RESULT_DELIMITER + StripUnits(lqstrResult);
   } else
   {
      lqstrResult = StripUnits(lqstrResult);
   }
   cerr << lqstrResult.toStdString() << endl;
   fqstrParsedResult.append( lqstrResult + "\r\n" );
}


void cParser_Sandra::ExtractProcessorArithmetic()
{
   const QString TEST_LABEL = "<<< Processor Arithmetic >>>";
   bool lboolLineFound = SkipToTestResults( TEST_LABEL );

   // Grab Aggregate Arithmetic Performance:
   ParseResult( "Aggregate Arithmetic (MOPS) ", lboolLineFound );
   // Grab Dhrystone:
   ParseResult( "Dhrystone (MIPS) ", lboolLineFound );
   // Grab Whetstone:
   ParseResult( "Whetstone (MFLOPS) ", lboolLineFound );
}

void cParser_Sandra::ExtractProcessorMultiMedia()
{
   const QString TEST_LABEL = "<<< Processor Multi-Media >>>";
   bool lboolLineFound = SkipToTestResults( TEST_LABEL );

   // Grab Aggregate Multimedia Performance:
   ParseResult( "Aggregate Multi-Media (MOPS) ", lboolLineFound );
   // Grab Multi-Media Int x8:
   ParseResult( "Multi-Media Int x8 (MIPS) ", lboolLineFound );
   // Grab Multi-Media Float x4:
   ParseResult( "Multi-Media Float x4 (MFLOPS) ", lboolLineFound );
   // Grab Multi-Media Double x2:
   ParseResult( "Multi-Media Double x2 (MFLOPS) ", lboolLineFound );
}

void cParser_Sandra::ExtractPowerManagement()
{
   const QString TEST_LABEL = "<<< Power Management Efficiency >>>";
   bool lboolLineFound = SkipToTestResults( TEST_LABEL );

   // Grab ALU Power Performance:
   ParseResult( "ALU Power Performance (MIPS) ", lboolLineFound );
   // Grab Power Efficiency:
   ParseResult( "Power Efficiency ", lboolLineFound );
}

void cParser_Sandra::ExtractCryptography()
{
   const QString TEST_LABEL = "<<< Cryptography >>>";
   bool lboolLineFound = SkipToTestResults( TEST_LABEL );

   ParseResult( "Cryptographic Bandwidth (MB/s) ", lboolLineFound );
   ParseResult( "AES256 (MB/s) ", lboolLineFound );
   ParseResult( "SHA256 (MB/s) ", lboolLineFound );
}

void cParser_Sandra::ExtractNetArithmetic()
{
   const QString TEST_LABEL = "<<< .NET Arithmetic >>>";
   bool lboolLineFound = SkipToTestResults( TEST_LABEL );

   ParseResult( "Aggregate .NET (MOPS) ", lboolLineFound );
   ParseResult( "Dhrystone .NET (MIPS) ", lboolLineFound );
   ParseResult( "Whetstone .NET (MFLOPS) ", lboolLineFound );
}

void cParser_Sandra::ExtractNetMultiMedia()
{
   const QString TEST_LABEL = "<<< .NET Multi-Media >>>";
   bool lboolLineFound = SkipToTestResults( TEST_LABEL );

   ParseResult( "Aggregate Multi-Media .NET (MPixel/s) ", lboolLineFound );
   ParseResult( "Multi-Media Int x1 .NET (MPixel/s) ", lboolLineFound );
   ParseResult( "Multi-Media Float x1 .NET (MPixel/s) ", lboolLineFound );
   ParseResult( "Multi-Media Double x1 .NET (MPixel/s) ", lboolLineFound );
}

void cParser_Sandra::ExtractVideoRendering()
{
   const QString TEST_LABEL = "<<< Video Rendering >>>";
   bool lboolLineFound = SkipToTestResults( TEST_LABEL );
   if( lboolLineFound )
   {
      lboolLineFound = SkipToTestResults( "Aggregate Shader (MPixel/s) " );
   }

   ParseResult("Aggregate Shader (MPixel/s) ", lboolLineFound );
   ParseResult("Dx10.1 (SM4.1) Float Shaders (MPixel/s) ", lboolLineFound );
   ParseResult("Dx10.1 (SM4.1) Double Shaders (MPixel/s) ", lboolLineFound );
}

void cParser_Sandra::ExtractFileSystems()
{
   const QString TEST_LABEL = "<<< File Systems >>>";
   bool lboolLineFound = SkipToTestResults( TEST_LABEL );

   ParseResult( "Drive Index (MB/s) ", lboolLineFound );
   QString lqstrReadLine = fInputTextStream.readLine(); //skip the next line
   ParseResult( "Random Access Time", lboolLineFound );
}

void cParser_Sandra::ExtractMemoryBandwidth()
{
   const QString TEST_LABEL = "<<< Memory Bandwidth >>>";
   bool lboolLineFound = SkipToTestResults( TEST_LABEL );

   ParseResult( "Aggregate Memory Performance (GB/s) ", lboolLineFound );
   ParseResult( "Int Buffered Memory Bandwidth (GB/s) ", lboolLineFound );
   ParseResult( "Float Buffered Memory Bandwidth (GB/s) ", lboolLineFound );
}

void cParser_Sandra::ExtractMemoryLatency()
{
   const QString TEST_LABEL = "<<< Memory Latency >>>";
   bool lboolLineFound = SkipToTestResults( TEST_LABEL );

   ParseResult( "Memory Latency (ns) ", lboolLineFound );
   ParseResult( "Speed Factor", lboolLineFound );
}

void cParser_Sandra::ExtractCacheAndMemory()
{
   const QString TEST_LABEL = "<<< Cache and Memory >>>";
   bool lboolLineFound = SkipToTestResults( TEST_LABEL );

   ParseResult( "Cache/Memory Bandwidth (GB/s) ", lboolLineFound );
   QString lqstrReadLine = fInputTextStream.readLine(); //skip the next line
   ParseResult( "Speed Factor", lboolLineFound );
   lqstrReadLine = fInputTextStream.readLine(); //skip the next line
   lqstrReadLine = fInputTextStream.readLine(); //skip the next line
   lqstrReadLine = fInputTextStream.readLine(); //skip the next line
   ParseResult( "L1 Data Cache (GB/s) ", lboolLineFound );
   ParseResult( "L2 On-board Cache (GB/s) ", lboolLineFound );
}

QString cParser_Sandra::StripUnits( QString aqstrFixUnits )
{
   const int ALL_UNITS = 12;
   const int BIG_UNITS = 3; // the first n elements need to be converted
   //const int LITTLE_UNITS = 1;
   const QString lqstrUnits[ ALL_UNITS ] =
      { "GOPS", "GIPS", "GFLOPS", "kPixels/s", "MPOS", "MIPS", "MFLOPS",
        "MPixel/s", "MB/s", "GB/s", "ns", "ms" };
   double ldResult = 0.0;
   QString lqstrResult = "0";

   QString lqstrUnitsReplaced = aqstrFixUnits;
   ldResult = aqstrFixUnits.toDouble();
   if( ldResult == 0 )
   {
      for( int i = 0; i < ALL_UNITS; i++ )
      {
         cerr << aqstrFixUnits.toStdString() << endl;
         aqstrFixUnits.replace( lqstrUnits[ i ], "" );
         cerr << aqstrFixUnits.toStdString() << endl;
         if( lqstrUnitsReplaced != aqstrFixUnits )
         {
            ldResult = aqstrFixUnits.toDouble();
            // bad unit was found, multiply by 1,000
            if( i < BIG_UNITS )
            {
               ldResult *= 1000;  // convert giga to mega
            }
            if( i == BIG_UNITS )
            {
               ldResult /= 1000;  // convert kilo to mega
            }
            break;
         }
      }
   }
   lqstrResult.setNum( ldResult );
   return  lqstrResult;
}
