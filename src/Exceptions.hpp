#pragma once
#include <exception>
class ServerException : std::exception {};
class HeaderNotFoundException : ServerException {}; 
class ParameterNotFoundException : ServerException {}; 
class InvalidRequest : ServerException {}; 
class EmptyRequest : ServerException {}; 
