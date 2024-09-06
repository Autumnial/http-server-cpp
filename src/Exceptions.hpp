#pragma once
#include <exception>
class ServerException : std::exception {};
class HeaderNotFoundException : ServerException {}; 
class ParameterNotFoundException : ServerException {}; 
class InvalidRoute : ServerException {}; 
class EmptyRequest : ServerException {}; 

