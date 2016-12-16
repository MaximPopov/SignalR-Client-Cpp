// Copyright (c) .NET Foundation. All rights reserved.
// Licensed under the Apache License, Version 2.0. See License.txt in the project root for license information.

#include "stdafx.h"
#include "default_websocket_client.h"

namespace signalr
{
    namespace
    {
        static web::websockets::client::websocket_client_config create_client_config(const std::unordered_map<utility::string_t, utility::string_t>& headers, bool validate_certificates)
        {
            web::websockets::client::websocket_client_config config;
            for (auto &header : headers)
            {
                config.headers()[header.first] = header.second;
            }
			config.set_validate_certificates(validate_certificates);

            return config;
        }
    }

    default_websocket_client::default_websocket_client(const std::unordered_map<utility::string_t, utility::string_t>& headers, bool validate_certificates)
        : m_underlying_client(create_client_config(headers, validate_certificates))
    { }

    pplx::task<void> default_websocket_client::connect(const web::uri &url)
    {
        return m_underlying_client.connect(url);
    }

    pplx::task<void> default_websocket_client::send(const utility::string_t &message)
    {
        web::websockets::client::websocket_outgoing_message msg;
        msg.set_utf8_message(utility::conversions::to_utf8string(message));
        return m_underlying_client.send(msg);
    }

    pplx::task<std::string> default_websocket_client::receive()
    {
        // the caller is responsible for observing exceptions
        return m_underlying_client.receive()
            .then([](web::websockets::client::websocket_incoming_message msg)
            {
                return msg.extract_string();
            });
    }

    pplx::task<void> default_websocket_client::close()
    {
        return m_underlying_client.close();
    }
}