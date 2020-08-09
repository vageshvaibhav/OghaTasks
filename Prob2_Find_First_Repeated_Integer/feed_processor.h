#include<fstream>
#include<iostream>
#include<sstream>
#include<unordered_map>
#include<memory>
#include<vector>
#include<set>
#include<climits>

using namespace std;
class FeedProcessor
{
    std::string m_input_file;
    int m_num_intermediate_files;
    public:
    FeedProcessor(const std::string& input_file,int number_of_smaller_intermediate_files=100)
        : m_input_file(input_file), m_num_intermediate_files(number_of_smaller_intermediate_files)
    {
    }

    ~FeedProcessor()
    {
        //Remove intermediate files created for intermediate results
        for (int i = 0; i < m_num_intermediate_files; i++)
        {   
            auto file_name = "output_" + to_string(i) + ".txt";
            remove(file_name.c_str());
        }
    }

    std::pair<int,int> GetFirstRepeatingNumber(const std::string& file_name)
    {
        unordered_map<int,int> already_read_map;
        ifstream input(file_name.c_str());
        std::string curr_value;
        vector<int> vec;
        while (input >> curr_value)
        {
            istringstream sstr(curr_value);
            string element;
            try
            {
                while(getline(sstr,element,','))
                {
                    vec.push_back(stoi(element));
                }
            }
            catch(...)
            {
                cout << "GetFirstRepeatingNumber: Parsing failed while converting number read from file to integer, returning";
                return make_pair(-1,-1);
            }
            auto iter = already_read_map.find(vec[0]);
            if (iter != already_read_map.end())
            {
                return make_pair(vec[0],vec[1]);
            }
            already_read_map[vec[0]] = vec[1];
            vec.clear();
        }
    //No repeating number found
    return make_pair(-1,-1);
}

    bool WriteEntryToBucketFileOnHashResult(int curr_value,int integer_index)
    {
        int hash_res = curr_value % 100;
        auto file_name = "output_" + to_string(hash_res) + ".txt";
        ofstream out_file;
        out_file.open(file_name.c_str(),std::ios_base::app);
        cout << curr_value << "," << integer_index << " written to temp file=" << file_name << endl;
        out_file << curr_value << "," << integer_index << endl;
        out_file.close();
        return true;
    }
    /* Read the data from the file. */
    /* The logic is to read the input integer file line by line
     *As contents of single file can not be loaded in to memory, 
     *hash every integer read to one of the intermediate files on the basic of modulo by 100(100 taken as default number)
     *Now, get first repeating integer from each file independently along with the index. Due to this, we are reducing 
     *number of elements loaded in to memory. This can be further reduced by increasing number of intermediate files more than 100
     *Finally merge all the results from small intermediate file to arrive the final result
     * i.e. first repeating integer
     * Did not use parallel processing for getting first repeating from different intermediate files as that could have lead to loading
     * more data at once.
     */
    int GetFirstRepeatingIntFromInputFile()
    {
        int first_repeating_number_index = INT_MAX;
        int first_repeating_number = INT_MAX;
        ifstream input(m_input_file.c_str());
        if(!input.is_open())
        {   
            cout<<"Unable to open input/output files"<<endl;
            return false;
        }   
        std::string curr_value;
        int curr_val_int;
        bool is_parsing_successful = true;
        int integer_index = 0;
        //Write each integer entry with index to smaller intermediate files using modulo hash
        try 
        {
            while (input >> curr_value && is_parsing_successful)
            {
                curr_val_int = stoi(curr_value);
                is_parsing_successful = WriteEntryToBucketFileOnHashResult(curr_val_int,integer_index);
                ++integer_index;
            }
        }
        catch(...)
        {
            cout << "GetFirstRepeatingIntFromInputFile: Parsing failed while converting number read from file to integer, returning";
            return first_repeating_number;
        }
        if (is_parsing_successful)
        {
            // Get first repeating number from all intermediate file and finally merge the results to get best candidate using original index
            // This step can be run across independent distributed machines in paralle but since we are running on current machine only 
            // This is done sequentially
            for (int i = 0; i < m_num_intermediate_files; i++)
            { 
                auto file_name = "output_" + to_string(i) + ".txt";
                auto res = GetFirstRepeatingNumber(file_name);
                if (res.second != -1 && res.second < first_repeating_number_index) //non negative index means a valid result
                {
                    first_repeating_number_index = res.second;
                    first_repeating_number = res.first;
                }
            }
        }
        return first_repeating_number;
    }
};
