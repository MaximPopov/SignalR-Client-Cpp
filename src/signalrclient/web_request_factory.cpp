// Copyright (c) .NET Foundation. All rights reserved.
// Licensed under the Apache License, Version 2.0. See License.txt in the project root for license information.

#include "stdafx.h"
#include "web_request_factory.h"
#include "make_unique.h"

namespace signalr
{
	web_request_factory::web_request_factory(bool validate_certificates)
		: m_validate_certificates(validate_certificates)
	{
	}

    std::unique_ptr<web_request> web_request_factory::create_web_request(const web::uri &url)
    {
        return std::make_unique<web_request>(url, m_validate_certificates);
    }

    web_request_factory::~web_request_factory()
    {}
}
