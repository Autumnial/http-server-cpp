
#include <exception>
class ServerException : std::exception {};
class HeaderNotFoundException : ServerException {}; 
class ParameterNotFoundException : ServerException {}; 
