#include <iostream>
#include <string>
#include <sstream>
#include <assert.h>
#include <fstream>

inline int convert_ss_to_num (const std::string& number_to_convert){
    //why does assert not work?
    assert(!number_to_convert.empty());
    
    std::stringstream str_stream;

    str_stream.clear();
    str_stream.str("");

    

    str_stream << number_to_convert;
    int number_value{0};
    str_stream >> number_value;

    if(str_stream.fail()){
        throw(std::runtime_error("Not a valid value"));
    }

    return(number_value);
}

inline bool is_password_valid (
    const int min_range, 
    const int max_range, 
    const char allowed_char, 
    const std::string& allowed_password){

        int number_of_occ{0};
        

        //assert(1 == allowed_char.length());
        //const char str_compar{allowed_char[0]};

        for(int index_str{0}; index_str != allowed_password.length(); ++index_str){
            if(allowed_char == allowed_password[index_str]){
                
                ++number_of_occ;
            }

            
        }

        bool is_valid{false};
        if(number_of_occ >= min_range && number_of_occ <= max_range){
                is_valid = true;
            }

    
    return(is_valid);
}

inline bool chop_up_string(const std::string& base_string){
    //std::string base_string = line;
    //expected format = "4-5 v: vcvhv"

    //extracting number range ex. 4-5
    std::size_t blank_space_first = base_string.find_first_of(' ', 0);
    std::string allowed_num = base_string.substr(0, blank_space_first);
    std::cout << allowed_num << '\n';

    
    std::size_t range_hyphen = allowed_num.find_first_of('-',0);
    std::string min_range_string = allowed_num.substr(0, range_hyphen);
    std::string max_range_string = allowed_num.substr(range_hyphen+1, std::string::npos);
    std::cout << min_range_string << " to " << max_range_string << '\n';
    const int min_range{convert_ss_to_num(min_range_string)};
    const int max_range{convert_ss_to_num(max_range_string)};
    std::cout << min_range << " and " << max_range << '\n';

    //password char example v
    constexpr int password_character_offset_from_blank_space{1};
    const char password_character{base_string[blank_space_first+password_character_offset_from_blank_space]};
    std::cout << password_character << '\n';

    //password example vvvvvvvvvg
    std::size_t blank_space_second = base_string.find_first_of(' ', blank_space_first + password_character_offset_from_blank_space);
    // auto colon_position = base_string.find_first_of(':');
    // if(base_string.npos == colon_position){
    //     throw(std::runtime_error("Did not find colon"));
    // }

    
    std::string allowed_password{base_string.substr(blank_space_second+password_character_offset_from_blank_space)};
    // constexpr auto password_offset_from_colon{2};
    // std::string allowed_password{base_string.substr(colon_position + password_offset_from_colon)};
    std::cout << allowed_password << '\n';

    // std::size_t blank_space_second = base_string.find_last_of(' ');
    // std::string allowed_char = base_string.substr(blank_space_second-2,1);
    // std::cout << allowed_char << '\n';
    // std::string allowed_password = base_string.substr(blank_space_second+1);
    // std::cout << allowed_password << '\n';

    bool valid_password{is_password_valid(min_range, max_range, password_character, allowed_password)};

    
    

    return(valid_password);
}

int calculate_correct_pw(const char *file_path){
    auto data_read{std::fstream(file_path)};

    if(!data_read.is_open()){
        throw(std::runtime_error("File is not open!"));
    }

    int if_correct{0};
    //assert still not working
    //assert(!data_read.empty());

    for(std::string line; !data_read.eof(); line.clear()){
        std::getline(data_read, line);




        if(data_read.fail()){
            assert(false);
            throw(std::runtime_error("Stream fail encountered"));
            
        }

        if (bool valid_password{chop_up_string(line)}){
            ++if_correct;
        } else {
            continue;
        }


    }

    return(if_correct);



}



int main(){

    

    try {
        constexpr auto file_path{"C:\\src\\code\\advent2020\\day2\\passwordpolicy.txt"};
        const int num_of_valid_pw{calculate_correct_pw(file_path)};
        std::cout << "There are: " << std::dec << num_of_valid_pw << " valid passwords." << '\n';
    } catch(const std::runtime_error& exception){
        std::cerr << exception.what() << '\n';
        return(EXIT_FAILURE);
    }

    

    return(EXIT_SUCCESS);
}
