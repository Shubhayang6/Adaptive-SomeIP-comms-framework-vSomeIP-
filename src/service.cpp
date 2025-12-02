#include <vsomeip/vsomeip.hpp>
#include <iostream>
#include <memory>

using namespace std;

#define SERVICE_ID  0x1234
#define INSTANCE_ID 0x5678
#define METHOD_ID   0x0421

shared_ptr<vsomeip::application> app;

void handle_request(const shared_ptr<vsomeip::message> request) {
    string received(
        reinterpret_cast<const char*>(request->get_payload()->get_data()),
        request->get_payload()->get_length()
    );

    cout << "[Service] Received request: " << received << endl;

    auto response = vsomeip::runtime::get()->create_response(request);
    string msg = "Hello from SOME/IP Service!";

    auto payload = vsomeip::runtime::get()->create_payload();
    payload->set_data(
        reinterpret_cast<const vsomeip::byte_t*>(msg.c_str()),
        msg.size()
    );

    response->set_payload(payload);
    app->send(response);

    cout << "[Service] Sent response." << endl;
}

int main() {
    app = vsomeip::runtime::get()->create_application("service-sample");

    if (!app->init()) {
        cerr << "Failed to init service app!" << endl;
        return 1;
    }

    app->register_message_handler(SERVICE_ID, INSTANCE_ID, METHOD_ID, handle_request);

    app->offer_service(SERVICE_ID, INSTANCE_ID);

    cout << "[Service] Offering service..." << endl;

    app->start();
    return 0;
}
