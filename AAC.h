//
// Created by Pedro on 13.03.2023.
//

#include <iostream>
#include <string>
#include <system_error>
#include <thread>
#include "enums.h"
#include "structs.h"

#ifndef AAC_H
#define AAC_H

/* -------------------------------------------------------------------------- */
/*                                 ERROR CODES                                */
/* -------------------------------------------------------------------------- */

// example usage of AAC library error codes
/*

FILE *open_file(const char *path) {
    FILE *f = fopen(path, "r");
    if(!f) {
        set_AAC_error_code(make_error_code(AAC_error_codes::INVALID_PATH));
        return NULL;
    }
    return f;
}

*/
// The error code is accessed outside of library ass follows
/*

int main(int argc, char *argv[]){
    FILE *new_file = open_file("new_file_path_invalid");
    if(!new_file) {
        std::cerr << get_AAC_error_code().message() << std::endl;
    }
    clear_AAC_error_code();
    // if above line is not run the error code is gonna stay untill
    // next error code overwrites it
}

*/

static thread_local std::error_code AAC_error_code;


void set_AAC_error_code(std::error_code ec);
std::error_code get_AAC_error_code();
void clear_AAC_error_code();


class AAC_error_category : public std::error_category 
{
public:
    virtual const char* name() const noexcept override {
        return "AAC_error_category";
    }

    virtual std::string message(int ec) const override {
        switch (static_cast<AAC_error_codes>(ec)){
            case AAC_error_codes::INVALID_PIXEL:
                return "Invalid pixel error";
            case AAC_error_codes::INVALID_PATH:
                return "Invalid image path";
            default:
                return "Unknown error";
        }
    }
};

const AAC_error_category AAC_category{};

std::error_code make_error_code(AAC_error_codes ec);

/* ------------------------------------ - ----------------------------------- */


/* -------------------------------------------------------------------------- */
/*                                 PIXEL CLASS                                */
/* -------------------------------------------------------------------------- */

template <AAC_Pixel_Type E>
class AAC_Pixel
{
private:
    const AAC_Pixel_Type _pixel_type = E;

};

/* -------------------------------------------------------------------------- */
/*                                 IMAGE CLASS                                */
/* -------------------------------------------------------------------------- */

class AAC_Image
{
private:
    const std::string _path;
    const int _size_x;
    const int _size_y;

    void *_data;

public:
    AAC_Image(std::string path, int size_x, int size_y, unsigned char *data, int n);

};


#endif //AAC_H
