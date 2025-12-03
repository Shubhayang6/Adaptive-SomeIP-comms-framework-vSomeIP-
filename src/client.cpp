#include <vsomeip/vsomeip.hpp>
#include <iostream>
#include <memory>

using namespace std;

#define CLIENT_APP_ID 0x2222
#define SERVICE_ID 0x1234
#define INSTANCE_ID 0x5678
#define METHOD_ID 0x0421

shared_ptr<vsomeip::application> app;

void on_response(const shared_ptr<vsomeip::message> response)
{
    string res(
        reinterpret_cast<const char *>(response->get_payload()->get_data()),
        response->get_payload()->get_length());

    cout << "[Client] Response Received: " << res << endl;
}

void send_request()
{
    cout << "[Client] Sending Request..." << endl;

    auto request = vsomeip::runtime::get()->create_request();

    request->set_service(SERVICE_ID);
    request->set_instance(INSTANCE_ID);
    request->set_method(METHOD_ID);

    string message = "Hello from Client";

    auto payload = vsomeip::runtime::get()->create_payload();

    payload->set_data(
        reinterpret_cast<const vsomeip::byte_t *>(message.c_str()),
        message.size());
    request->set_payload(payload);

    app->send(request);
}

void on_availability(vsomeip::service_t _service, vsomeip::instance_t _instance, bool _is_available)
{
    cout << "[Client] Service [" << hex << _service << "." << _instance << "] is "
         << (_is_available ? "available." : "NOT available.") << endl;
    
    if (_is_available)
    {
        send_request();
    }
}

void on_state(vsomeip::state_type_e state)
{
    if (state == vsomeip::state_type_e::ST_REGISTERED)
    {
        cout << "[Client] Registered - waiting for service availability..." << endl;
    }
}

int main()
{
    app = vsomeip::runtime::get()->create_application("client-sample");

    if (!app->init())
    {
        cerr << "Failed to init client app!" << endl;
        return 1;
    }

    app->register_state_handler(on_state);
    app->register_availability_handler(SERVICE_ID, INSTANCE_ID, on_availability);
    app->register_message_handler(SERVICE_ID, INSTANCE_ID, METHOD_ID, on_response);

    app->request_service(SERVICE_ID, INSTANCE_ID);

    cout << "[Client] Waiting for service..." << endl;

    app->start();
    return 0;
}