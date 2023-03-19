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
                return "[AAC] Invalid pixel";
            case AAC_error_codes::INVALID_PATH:
                return "[AAC] Invalid path";
            case AAC_error_codes::INVALID_ARGUMENTS:
                return "[AAC] Invalid arguments";
            default:
                return "[AAC] Unknown error";
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
    const int _n;

    void *_data;

    // helper for constructor
    // convers raw data to an array of appropriet size and AAC pixel types
    

public:
    const AAC_Pixel_Type pixel_type;

    AAC_Image(std::string path, int size_x, int size_y, int n, unsigned char *data);

};


#endif //AAC_H
