#include <iostream>
#include <EGE.hpp>

using namespace EGE;

int main()
{
	Logger::AddMessage("Hello!", LogType::Note);
	Logger::AddMessage("This is an error message.", LogType::Error);
	Logger::AddMessage("This is another error message.", LogType::Error);
	Logger::AddMessage("This is a success message.", LogType::Success);
	Logger::AddMessage("Note message.", LogType::Note);
	Logger::AddMessage("Warning message.", LogType::Warning);
	Logger::AddMessage("Warning message.", LogType::Warning);

	LogType Type;
	while ((Type = Logger::HasPendingMessage()) != LogType::None)
		std::cout << Logger::GetFirstMessage(Type) << std::endl;

	return 0;
}