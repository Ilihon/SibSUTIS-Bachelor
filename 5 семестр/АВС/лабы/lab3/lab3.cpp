#include <chrono>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>
#include <regex>

enum MemoryType {
    RAM, HD
};

struct Arguments {
    MemoryType memory_type{};
    int block_size{};
    int alloc_size{};
    int launch_amount{};
    std::string filepath{};
};

MemoryType parse_memory_type(std::string &str) {
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    if (str == "RAM")
        return MemoryType::RAM;
    else if (str == "HD")
        return MemoryType::HD;
    else
        throw std::runtime_error("Incorrect memory type");
}

int parse_block_size(std::string &str) {
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    std::cmatch cm;
    std::regex regex = std::regex(R"(^(\d+)((K|M)?)$)", std::regex_constants::icase);
    if (!std::regex_match(str.c_str(), cm, regex))
        throw std::runtime_error("Incorrect block size");

    int value = std::stoi(cm[1]);
    std::string type = cm[2];
    if (type.empty())
        return value;
    else if (type == "K")
        return value * (1 << 10);
    else
        return value * (1 << 20);
}

void parse_arguments(std::vector<std::string> &args, Arguments *arg_struct) {
    if (args.size() >= 3) {
        arg_struct->memory_type = parse_memory_type(args[0]);
        arg_struct->block_size = parse_block_size(args[1]);
        arg_struct->launch_amount = std::stoi(args[2]);
        if (arg_struct->block_size > (4 * (1 << 20)))
            arg_struct->alloc_size = 4 * (1 << 20);
        else
            arg_struct->alloc_size = arg_struct->block_size;
        if (args.size() >= 4 && arg_struct->memory_type == MemoryType::HD) {
            arg_struct->filepath = args[3];
        }
    } else {
        throw std::runtime_error("You must provide memory type, block size and launch amount");
    }
}

std::vector<long long> benchmark_ram_write(int block_size, int alloc_size, int repeats) {
    auto results = std::vector<long long>();
    for (unsigned int i = 0; i < repeats; ++i) {
        uint8_t *arr;
        int counter = 0;
        auto start_time = std::chrono::high_resolution_clock::now();
        //
        while (counter < block_size) {
            arr = new uint8_t[alloc_size];
            counter += alloc_size;
        }
        //
        auto end_time = std::chrono::high_resolution_clock::now();
        delete[] arr;
        auto elapsed_time = end_time - start_time;
        long long microseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_time).count();
        results.push_back(microseconds);
    }

    return results;
}

std::vector<long long> benchmark_hd_write(int block_size, int alloc_size, int repeats, std::string filename) {
    auto results = std::vector<long long>();
    uint8_t arr[alloc_size];
    for (unsigned int i = 0; i < repeats; ++i) {
        for (int j = 0; j < alloc_size; ++j) {
            arr[j] = rand() % (1 << 8);
        }
        int counter = 0;
        auto f_out = std::ofstream(filename, std::ios::binary | std::ios::trunc);
        auto start_time = std::chrono::high_resolution_clock::now();
        //
        while (counter < block_size) {
            f_out.write(reinterpret_cast<const char *>(arr), sizeof(arr));
            counter += alloc_size;
        }
        //
        auto end_time = std::chrono::high_resolution_clock::now();
        f_out.close();
        auto elapsed_time = end_time - start_time;
        long long microseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_time).count();
        results.push_back(microseconds);
    }

    return results;
}

std::vector<long long> benchmark_hd_read(int block_size, int alloc_size, int repeats, std::string filename) {
    auto results = std::vector<long long>();
    uint8_t arr[alloc_size];
    for (unsigned int i = 0; i < repeats; ++i) {
        for (int j = 0; j < alloc_size; ++j) {
            arr[j] = rand() % (1 << 8);
        }
        auto f_out = std::fstream(filename, std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
        int counter = 0;
        while (counter < block_size) {
            f_out.write(reinterpret_cast<const char *>(arr), sizeof(arr));
            counter += alloc_size;
        }
        f_out.close();
        f_out = std::fstream(filename, std::ios::in | std::ios::binary);
        auto start_time = std::chrono::high_resolution_clock::now();
        //
        while (!f_out.eof()) {
            f_out.read(reinterpret_cast<char *>(arr), sizeof(arr));
        }
        //
        auto end_time = std::chrono::high_resolution_clock::now();
        f_out.close();
        auto elapsed_time = end_time - start_time;
        long long microseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_time).count();
        results.push_back(microseconds);
    }

    return results;
}

void print_result_ram(const std::vector<long long> &results, int block_size, int alloc_size) {
    std::cout << "MemoryType" << ",";
    std::cout << "BlockSize" << ",";
    std::cout << "ElementType" << ",";
    std::cout << "BufferSize" << ",";
    std::cout << "LaunchNum" << ",";
    std::cout << "Timer" << ",";
    std::cout << "WriteTime" << ",";
    std::cout << "ReadTime" << std::endl;
    for (int i = 0; i < results.size(); ++i) {
        std::cout << "RAM" << ",";
        std::cout << block_size << ",";
        std::cout << "byte" << ",";
        std::cout << alloc_size << ",";
        std::cout << i + 1 << ",";
        std::cout << "chrono" << ",";
        std::cout << results[i] << ",";
        std::cout << "NaN" << std::endl;
    }
}

void print_result_hd(const std::vector<long long> &write, const std::vector<long long> &read, int block_size,
                     int alloc_size) {
    std::cout << "MemoryType" << ",";
    std::cout << "BlockSize" << ",";
    std::cout << "ElementType" << ",";
    std::cout << "BufferSize" << ",";
    std::cout << "LaunchNum" << ",";
    std::cout << "Timer" << ",";
    std::cout << "WriteTime" << ",";
    std::cout << "ReadTime" << std::endl;
    for (int i = 0; i < write.size(); ++i) {
        std::cout << "RAM" << ",";
        std::cout << block_size << ",";
        std::cout << "byte" << ",";
        std::cout << alloc_size << ",";
        std::cout << i + 1 << ",";
        std::cout << "chrono" << ",";
        std::cout << write[i] << ",";
        std::cout << read[i] << std::endl;
    }
}

int main(int argc, char *argv[]) {
    // PARSE ARGUMENTS
    std::vector<std::string> arg_list;
    arg_list.reserve(argc);
    for (int i = 1; i < argc; ++i) {
        arg_list.emplace_back(std::string(argv[i]));
    }
    auto args = Arguments();
    parse_arguments(arg_list, &args);
    // PARSE ARGUMENTS

    if (args.memory_type == MemoryType::RAM) {
        print_result_ram(benchmark_ram_write(args.block_size, args.alloc_size, args.launch_amount), args.block_size,
                         args.alloc_size);
    } else {
        print_result_hd(benchmark_hd_write(args.block_size, args.alloc_size, args.launch_amount, args.filepath),
                        benchmark_hd_write(args.block_size, args.alloc_size, args.launch_amount, args.filepath),
                        args.block_size, args.alloc_size);
    }

    return 0;
}
