#include <sys/errno.h>
#include <stdio.h>
#include <stdexcept>
#include <string.h>
#include <stdlib.h>
#include <cerrno>
#include <cstdio>

#define SBB_LINE_BUFFER_LENGTH 256
#define SBB_INSTRUMENT_ID_LENGTH 32
#define SBB_TICKET_LENGTH 2

// wide open class for loading data per instrument
class SBB_instrument_fields {
public:
    SBB_instrument_fields(){
        SecurityID[0]=0;
        SettlementDate=0;
        CouponRate=0.0;
        MaturityDate=0;
        Frequency=0;
        RateType="";
        YieldRate=0.0;
        Quality="";
        Amount = 0.0;
    } 
    ~SBB_instrument_fields() {};
    
    void show(){
        
        printf("ID: %s Ticker %s SettleDate: %d Coupon: %.2f MatDate: %d Frequency: %d Yield: %.3f \n",
               SecurityID,
               Ticker,
               SettlementDate,
               CouponRate,
               MaturityDate,
               Frequency,
               YieldRate);
    }
    
    char SecurityID[SBB_INSTRUMENT_ID_LENGTH];
    char Ticker[SBB_TICKET_LENGTH];
    int SettlementDate;
    double CouponRate;
    int MaturityDate;
    short Frequency;
    std::string RateType;
    
    double YieldRate;
    std::string Quality;
    double Amount;
};

// simple class for interfacing with data file that contains instrument desriptive data 
// (and yield)
class SBB_instrument_input_file {
    
	// Resource (file handle) acquisition is initialization version - "RAII"
	// destructor closes file...
public:
    SBB_instrument_input_file(const char* filename);
    ~SBB_instrument_input_file();
    
    //
    // once his object is contructed (and the file is open), returns number of items in it
    //
    int get_record_count();
	
    //
    // returns a heap allocated array of file contents
    //
    SBB_instrument_fields* get_records(int& length);
    
    //
    // As a convenience to the caller memory is allocated inside this class
    // Call this to free it
    //
    void free_records();
    
private:
    std::FILE *_file;
    char _line_buf[SBB_LINE_BUFFER_LENGTH];
    SBB_instrument_fields *_fields_array;
    
    //
    // prevent copying
    // 
    SBB_instrument_input_file (const SBB_instrument_input_file &);
    
    //
    // prevent assignment
    //
    SBB_instrument_input_file & operator= (const SBB_instrument_input_file &);
    
    //
    // disable the default constructor
    // force construction with filename param only...
    //
    SBB_instrument_input_file();
};
