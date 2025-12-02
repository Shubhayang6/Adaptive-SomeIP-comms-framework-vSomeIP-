#include <vsomeip/vsomeip.hpp>
#include <iostream>
#include <memory>

using namespace std;

#define SERVICE_ID 0x1234
#define INSTANCE_ID 0x5678
#define CLIENT_ID 0x0421

shared_ptr<vsomeip::application> app;

void on_response(const shared_ptr<vsomeip::message> response)
{
    string res(
        reinterpret_cast<const char*>(response->get_payload()->get_data()),
        response->get_payload()->get_length()
    );
}