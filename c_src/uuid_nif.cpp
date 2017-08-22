#include "erl_nif.h"

#include "uuid.hpp"

#include <iostream>
#include <vector>


static ERL_NIF_TERM
base58_decode_nif(ErlNifEnv* env, int argc,
                  const ERL_NIF_TERM argv[])
{
    ErlNifBinary input, output;

    if (argc == 1) {
        if (enif_inspect_iolist_as_binary(env, argv[0], &input)) {
            if (input.size > 0) {
                std::vector<unsigned char> input_vector;
                for (uint8_t i = 0; i < input.size; i++)
                    input_vector.push_back(input.data[i]);
                std::string input_id(input_vector.begin(), input_vector.end());
                UUID::uuid id = UUID::base58_decode(input_id, UUID::Endianness::Big);
                std::string sid = UUID::serialize(id);
                enif_alloc_binary(sid.length(), &output);
                const char* out = sid.c_str();
                for (uint8_t i = 0; i < sid.length(); i++)
                    output.data[i] = out[i];
                return enif_make_binary(env, &output);
            };
        };
    };
    return enif_make_badarg(env);
}

static ERL_NIF_TERM
base58_encode_nif(ErlNifEnv* env, int argc,
                  const ERL_NIF_TERM argv[])
{
    ErlNifBinary input, output;

    if (argc == 1) {
        if (enif_inspect_iolist_as_binary(env, argv[0], &input)) {
            if (input.size > 0) {
                std::vector<unsigned char> input_vector;
                for (uint8_t i = 0; i < input.size; i++)
                    input_vector.push_back(input.data[i]);
                std::string input_id(input_vector.begin(), input_vector.end());
                UUID::uuid id   = UUID::parse(input_id);
                std::string sid = UUID::base58_encode(id, UUID::Endianness::Big);
                enif_alloc_binary(sid.length(), &output);
                const char* out = sid.c_str();
                for (uint8_t i = 0; i < sid.length(); i++)
                    output.data[i] = out[i];
                return enif_make_binary(env, &output);
            };
        };
    };
    return enif_make_badarg(env);
}

typedef struct {
    unsigned char u[22];
} base58_uuid_t;

static ERL_NIF_TERM
generate_base58_nif(ErlNifEnv* env, int argc,
                    const ERL_NIF_TERM argv[])
{
    std::string uid = UUID::generate_base58();
    uint8_t size = uid.length();
    const char* id = uid.c_str();
    base58_uuid_t *q;
    ERL_NIF_TERM ret;
    q = (base58_uuid_t*) enif_make_new_binary(env, size, &ret);
    memcpy(q, id, size);
    return ret;
}

typedef struct {
    unsigned char u[36];
} uuid_t;

static ERL_NIF_TERM
generate_uuid_nif(ErlNifEnv* env, int argc,
                  const ERL_NIF_TERM argv[])
{
    std::string uid = UUID::generate_string();
    const char* id = uid.c_str();
    base58_uuid_t *q;
    ERL_NIF_TERM ret;
    q = (base58_uuid_t*) enif_make_new_binary(env, 36, &ret);
    memcpy(q, id, 36);
    return ret;
}

static ErlNifFunc nif_funcs[] = {
    {"base58_decode",   1, base58_decode_nif},
    {"base58_encode",   1, base58_encode_nif},
    {"generate",        0, generate_uuid_nif},
    {"generate_base58", 0, generate_base58_nif}
};

ERL_NIF_INIT(uuid, nif_funcs, NULL, NULL, NULL, NULL)
