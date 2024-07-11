#include "Enums.hpp"

Method method_from_string(std::string method_string) {
    if (method_string == "GET") {
        return Method::GET;
    } else if (method_string == "POST") {
        return Method::POST;
    } else if (method_string == "PUT") {
        return Method::PUT;
    } else if (method_string == "DELETE") {
        return Method::DELETE;
    } else if (method_string == "HEAD") {
        return Method::HEAD;
    } else if (method_string == "OPTIONS") {
        return Method::OPTIONS;
    } else if (method_string == "PATCH") {
        return Method::PATCH;
    } else if (method_string == "CONNECT") {
        return Method::CONNECT;
    } else if (method_string == "TRACE") {
        return Method::TRACE;
    } else {
        return Method::UNDEFINED;
    }
}

std::string status_to_string(StatusCode status) {
    switch (status) {
    case CONTINUE: {
        return "100 Continue";
    }
    case SWITCHING_PROTOCOLS: {
        return "101 Switching Protocols";
    }
    case PROCESSING: {
        return "102 Processing";
    }
    case EARLY_HINTS: {
        return "103 Early Hints";
    }
    case OK: {
        return "200 Ok";
    }
    case CREATED: {
        return "201 Created";
    }
    case ACCEPTED: {
        return "202 Accepted";
    }
    case NON_AUTHORITATIVE_INFORMATION: {
        return "203 Non Authoritative Information";
    }
    case NO_CONTENT: {
        return "204 No Content";
    }
    case RESET_CONTENT: {
        return "205 Reset Content";
    }
    case PARTIAL_CONTENT: {
        return "206 Partial Content";
    }
    case MULTI_STATUS: {
        return "207 Multi Status";
    }
    case ALREADY_REPORTED: {
        return "208 Already Reported";
    }
    case IM_USED: {
        return "226 Im Used";
    }
    case MULTIPLE_CHOICES: {
        return "300 Multiple Choices";
    }
    case MOVED_PERMANENTLY: {
        return "301 Moved Permanently";
    }
    case FOUND: {
        return "302 Found";
    }
    case SEE_OTHER: {
        return "303 See Other";
    }
    case NOT_MODIFIED: {
        return "304 Not Modified";
    }
    case USE_PROXY: {
        return "305 Use Proxy";
    }
    case TEMPORARY_REDIRECT: {
        return "307 Temporary Redirect";
    }
    case PERMANENT_REDIRECT: {
        return "308 Permanent Redirect";
    }
    case BAD_REQUEST: {
        return "400 Bad Request";
    }
    case UNAUTHORIZED: {
        return "401 Unauthorized";
    }
    case PAYMENT_REQUIRED: {
        return "402 Payment Required";
    }
    case FORBIDDEN: {
        return "403 Forbidden";
    }
    case NOT_FOUND: {
        return "404 Not Found";
    }
    case METHOD_NOT_ALLOWED: {
        return "405 Method Not Allowed";
    }
    case NOT_ACCEPTABLE: {
        return "406 Not Acceptable";
    }
    case PROXY_AUTHENTICATION_REQUIRED: {
        return "407 Proxy Authentication Required";
    }
    case REQUEST_TIMEOUT: {
        return "408 Request Timeout";
    }
    case CONFLICT: {
        return "409 Conflict";
    }
    case GONE: {
        return "410 Gone";
    }
    case LENGTH_REQUIRED: {
        return "411 Length Required";
    }
    case PRECONDITION_FAILED: {
        return "412 Precondition Failed";
    }
    case PAYLOAD_TOO_LARGE: {
        return "413 Payload Too Large";
    }
    case URI_TOO_LONG: {
        return "414 Uri Too Long";
    }
    case UNSUPPORTED_MEDIA_TYPE: {
        return "415 Unsupported Media Type";
    }
    case RANGE_NOT_SATISFIABLE: {
        return "416 Range Not Satisfiable";
    }
    case EXPECTATION_FAILED: {
        return "417 Expectation Failed";
    }
    case IM_A_TEAPOT: {
        return "418 Im A Teapot";
    }
    case MISDIRECTED_REQUEST: {
        return "421 Misdirected Request";
    }
    case UNPROCESSABLE_ENTITY: {
        return "422 Unprocessable Entity";
    }
    case LOCKED: {
        return "423 Locked";
    }
    case FAILED_DEPENDENCY: {
        return "424 Failed Dependency";
    }
    case TOO_EARLY: {
        return "425 Too Early";
    }
    case UPGRADE_REQUIRED: {
        return "426 Upgrade Required";
    }
    case PRECONDITION_REQUIRED: {
        return "428 Precondition Required";
    }
    case TOO_MANY_REQUESTS: {
        return "429 Too Many Requests";
    }
    case REQUEST_HEADER_FIELDS_TOO_LARGE: {
        return "431 Request Header Fields Too Large";
    }
    case UNAVAILABLE_FOR_LEGAL_REASONS: {
        return "451 Unavailable For Legal Reasons";
    }
    case INTERNAL_SERVER_ERROR: {
        return "500 Internal Server Error";
    }
    case NOT_IMPLEMENTED: {
        return "501 Not Implemented";
    }
    case BAD_GATEWAY: {
        return "502 Bad Gateway";
    }
    case SERVICE_UNAVAILABLE: {
        return "503 Service Unavailable";
    }
    case GATEWAY_TIMEOUT: {
        return "504 Gateway Timeout";
    }
    case HTTP_VERSION_NOT_SUPPORTED: {
        return "505 Http Version Not Supported";
    }
    case VARIANT_ALSO_NEGOTIATES: {
        return "506 Variant Also Negotiates";
    }
    case INSUFFICIENT_STORAGE: {
        return "507 Insufficient Storage";
    }
    case LOOP_DETECTED: {
        return "508 Loop Detected";
    }
    case NOT_EXTENDED: {
        return "510 Not Extended";
    }
    case NETWORK_AUTHENTICATION_REQUIRED: {
        return "511 Network Authentication Required";
    }
    default: {
        exit(-1);
    }
    }
}
