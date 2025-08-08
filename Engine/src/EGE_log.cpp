#include <EGE_log.hpp>

namespace EGE
{
	std::mutex Logger::Mutex;
	std::queue<std::string> Logger::ErrorMessages;
	std::queue<std::string> Logger::WarningMessages;
	std::queue<std::string> Logger::NoteMessages;
	std::queue<std::string> Logger::SuccessMessages;
	size_t Logger::MessageCount = 0;

	std::queue<std::string>* Logger::GetQueueOfType(LogType Type)
	{
		switch (Type)
		{
		case LogType::Error:
			return &ErrorMessages;
			break;

		case LogType::Warning:
			return &WarningMessages;
			break;

		case LogType::Note:
			return &NoteMessages;
			break;

		case LogType::Success:
			return &SuccessMessages;
			break;

		default:
			//An invalid LogType was given
			return nullptr;
			break;
		}
	}

	std::string Logger::GetFirstMessage(LogType Type)
	{
		//This makes the function thread-safe by elimitating race conditions
		std::lock_guard<std::mutex> lock(Mutex);

		std::queue<std::string>* MessageQueue = GetQueueOfType(Type);
	
		if (MessageQueue == nullptr || MessageQueue->empty())
		{
			//The queue is empty
			return "";
		}
		
		std::string Message = MessageQueue->front(); //Retrieve message
		MessageQueue->pop(); //Pop the message so that it is no longer in the queue
		MessageCount--;
		return Message;
	}

	bool Logger::AddMessage(const std::string& Message, LogType Type)
	{
		//This makes the function thread-safe by elimitating race conditions
		std::lock_guard<std::mutex> lock(Mutex);

		//Message length check
		if (Message.size() > MaxMessageSize)
		{
			return false;
		}

		std::queue<std::string>* MessageQueue = GetQueueOfType(Type);

		if (MessageQueue == nullptr)
		{
			return false;
		}

		//Check if the message count is already at its max value
		if (MessageCount > MaxMessages)
		{
			return false;
		}

		MessageQueue->push(Message);

		MessageCount++;
		return true;
	}

	LogType Logger::HasPendingMessage()
	{
		if (!ErrorMessages.empty())
			return LogType::Error;

		else if (!WarningMessages.empty())
			return LogType::Warning;

		else if (!NoteMessages.empty())
			return LogType::Note;

		else if (!SuccessMessages.empty())
			return LogType::Success;

		else
			return LogType::None;
	}
}