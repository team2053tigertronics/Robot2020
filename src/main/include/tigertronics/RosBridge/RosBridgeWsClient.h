#pragma once

#include "WsClient.h"

#include <wpi/json.h>

class RosBridgeWsClient
{
public:
	RosBridgeWsClient();

	void Advertise(const std::string& client_name, const std::string& topic, const std::string& type, const std::string& id = "") {
		std::string message = "\"op\":\"advertise\", \"topic\":\"" + topic + "\", \"type\":\"" + type + "\"";
		if (id.compare("") != 0)
		{
			message += ", \"id\":\"" + id + "\"";
		}
		message = "{" + message + "}";
		endpoint.connect(connection_uri, client_name, nullptr, nullptr, nullptr, nullptr);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		endpoint.send(client_name, message);
		endpoint.connect(connection_uri, "publish_client" + client_name, nullptr, nullptr, nullptr, nullptr);
	}

	void Publish(const std::string& client_name, const std::string& topic, const wpi::json& msg, const std::string& id = "") {
		std::string message = "\"op\":\"publish\", \"topic\":\"" + topic + "\", \"msg\":" + msg.dump();
		if (id.compare("") != 0)
		{
			message += ", \"id\":\"" + id + "\"";
		}
		message = "{" + message + "}";
		endpoint.send("publish_client" + client_name, message);
	}

	void Subscribe(const std::string& client_name, const std::string& topic, const std::function<void(client * c, websocketpp::connection_hdl hdl, client::message_ptr msg)>& callback, const std::string& id = "", const std::string& type = "", int throttle_rate = -1, int queue_length = -1, int fragment_size = -1, const std::string& compression = "") {
		std::string message = "\"op\":\"subscribe\", \"topic\":\"" + topic + "\"";

		if (id.compare("") != 0)
		{
			message += ", \"id\":\"" + id + "\"";
		}
		if (type.compare("") != 0)
		{
			message += ", \"type\":\"" + type + "\"";
		}
		if (throttle_rate > -1)
		{
			message += ", \"throttle_rate\":" + std::to_string(throttle_rate);
		}
		if (queue_length > -1)
		{
			message += ", \"queue_length\":" + std::to_string(queue_length);
		}
		if (fragment_size > -1)
		{
			message += ", \"fragment_size\":" + std::to_string(fragment_size);
		}
		if (compression.compare("none") == 0 || compression.compare("png") == 0)
		{
			message += ", \"compression\":\"" + compression + "\"";
		}
		message = "{" + message + "}";

		endpoint.connect(connection_uri, client_name, nullptr, nullptr, nullptr, callback);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		endpoint.send(client_name, message);
	}

	void AdvertiseService(const std::string& client_name, const std::string& service, const std::string& type, const std::function<void(client * c, websocketpp::connection_hdl hdl, client::message_ptr msg)>& callback) {
		std::string message = "{\"op\":\"advertise_service\", \"service\":\"" + service + "\", \"type\":\"" + type + "\"}";
		endpoint.connect(connection_uri, client_name, nullptr, nullptr, nullptr, callback);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		endpoint.send(client_name, message);
	}

	void ServiceResponse(const std::string& service, const std::string& id, bool result, const wpi::json& values = {}) {
		std::string message = "\"op\":\"service_response\", \"service\":\"" + service + "\", \"result\":" + ((result) ? "true" : "false");
		message += ", \"id\":\"" + id + "\"";
		message += ", \"values\":" + std::string(values.dump());
		message = "{" + message + "}";

		std::function<void(client * c, websocketpp::connection_hdl hdl)> openFunc = [message,this](client* c, websocketpp::connection_hdl hdl) {
			endpoint.send("service_response_client", message);
			endpoint.close("service_response_client", websocketpp::close::status::normal, "Service Over");
		};
		endpoint.connect(connection_uri, "service_response_client", openFunc, nullptr, nullptr, nullptr);
	}

	void CallService(const std::string& service, const std::function<void(client * c, websocketpp::connection_hdl hdl, client::message_ptr msg)>& callback, const wpi::json& args = {}, const std::string& id = "", int fragment_size = -1, const std::string& compression = "") {
		std::string message = "\"op\":\"call_service\", \"service\":\"" + service + "\"";
		if (!args.is_null())
		{
			message += ", \"args\":" + std::string(args.dump());
		}
		if (id.compare("") != 0)
		{
			message += ", \"id\":\"" + id + "\"";
		}
		if (fragment_size > -1)
		{
			message += ", \"fragment_size\":" + std::to_string(fragment_size);
		}
		if (compression.compare("none") == 0 || compression.compare("png") == 0)
		{
			message += ", \"compression\":\"" + compression + "\"";
		}
		message = "{" + message + "}";

		endpoint.connect(connection_uri, "call_service_client", nullptr, nullptr, nullptr, callback);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		endpoint.send("call_service_client", message);
	}

	void SetConnectionUri(std::string uri) {
		connection_uri = uri;
	}
private:
	std::string connection_uri;
	websocket_endpoint endpoint;
};