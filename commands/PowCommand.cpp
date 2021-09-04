//
// Created by fali on 01/08/2021.
//
#include <iostream>
#include <chrono>
#include "PowCommand.h"
#include "../utils.h"
#include "Combinations.h"

PowCommand::PowCommand(Connection *connection, int num_threads) {
    this->connection = connection;
    this->num_threads = num_threads;
    this->global_seed = (unsigned) time(NULL);

    // TODO how to generate UTF-8 strings
    this->charset = string(
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "!@#$%^&*()_+-={}[];':"
            "\"/\\|?.,><~");
    //"`ñáéíóúźćǘńḿẃŕýúṕÁÉÍÓÚŹĆǗŃḾẂŔÝṔ¨");
}

PowCommand::~PowCommand() {}

/*string PowCommand::gen_random_string(const int len, unsigned int *seed) {
    string random_str;
    random_str.reserve(len);

    for (int i = 0; i < len; ++i) {
        random_str += charset.at(rand_r(seed) % (charset.length() - 1));
    }
    return random_str;
}*/


void PowCommand::find_prefix(int threadid, string authdata, int leading_zeros) {
    long i = 0;

    auto begin = chrono::high_resolution_clock::now();
    auto end = chrono::high_resolution_clock::now();
    double duration = chrono::duration<double>(end - begin).count();

    unsigned char hash[SHA_DIGEST_LENGTH];
    int max_leading_zeros = 0;
    string max_leading_zeros_suffix;

    //unsigned int local_seed = threadid * rand_r(&this->global_seed) * time(NULL);
    //cout << "Threadid=" << threadid << " seed=" << local_seed << " start. " << endl;

    int init_index = (charset.length()/num_threads) * threadid;
    Combinations combinations(12, charset, init_index);

    while (!found && combinations.hasNext()) {
        //string suffix = gen_random_string( 8 + threadid, &local_seed);
        string suffix = combinations.next();


        if (duration > DELTA) {
            printf("thid=%2d suffix=%32s rate=%6.2f k/s max_leading_sofar=%s \n", threadid, suffix.c_str(), (i / DELTA),
                   max_leading_zeros_suffix.c_str());
            begin = chrono::high_resolution_clock::now();
            i = 0;
        }

        string data(authdata + suffix);
        SHA1((const unsigned char *) data.c_str(), data.length(), hash);

        int num_leading_zeros = 0;
        for (unsigned char c : hash) {
            if (c == 0) {
                num_leading_zeros += 2;
            } else if (c >> 4 == 0) {
                num_leading_zeros += 1;
                break;
            } else {
                break;
            }
        }

        if (num_leading_zeros >= max_leading_zeros) {
            max_leading_zeros = num_leading_zeros;
            max_leading_zeros_suffix = string(to_hex(hash, SHA_DIGEST_LENGTH));
        }

        if (num_leading_zeros >= leading_zeros) {
            this->suffix = suffix;
            this->found = true;
        }

        end = chrono::high_resolution_clock::now();
        duration = chrono::duration<double>(end - begin).count();
        i++;
    }

    printf("End thread %d\n", threadid);
}

bool PowCommand::apply(map<string, string> *context, string **args, int num_args) {
    string authdata = *args[1];
    string difficulty = *args[2];

    context->emplace("authdata", string(authdata));
    context->emplace("difficulty", string(difficulty));

    cout << "authdata=" << authdata << endl;
    cout << "difficulty=" << difficulty << endl;

    int leading_zeros = atoi(difficulty.c_str());

    auto begin = chrono::high_resolution_clock::now();
    this->found = false;

    thread *hash_generators[num_threads];
    for (int i = 0; i < num_threads; ++i) {
        hash_generators[i] = new thread(&PowCommand::find_prefix, this, i, authdata, leading_zeros);
    }

    for (int i = 0; i < num_threads; ++i) {
        hash_generators[i]->join();
    }

    for (int i = 0; i < num_threads; ++i) {
        delete hash_generators[i];
    }


    auto end = chrono::high_resolution_clock::now();
    double duration = chrono::duration<double>(end - begin).count();

    cout << "Found suffix=" << this->suffix << " in " << duration << " s" << endl;
    connection->write(suffix + "\n");
    return false;
}
