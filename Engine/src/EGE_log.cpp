#include <EGE_log.hpp>

namespace EGE
{
	std::mutex Logger::m_Mutex;
	std::queue<std::string> Logger::m_ErrorMessages;
	std::queue<std::string> Logger::m_WarningMessages;
	std::queue<std::string> Logger::m_NoteMessages;
	std::queue<std::string> Logger::m_SuccessMessages;
	size_t Logger::m_MessageCount = 0;

	std::queue<std::string>* Logger::GetQueueOfType(LogType Type)
	{
		switch (Type)
		{
		case LogType::Error:
			return &m_ErrorMessages;
			break;

		case LogType::Warning:
			return &m_WarningMessages;
			break;

		case LogType::Note:
			return &m_NoteMessages;
			break;

		case LogType::Success:
			return &m_SuccessMessages;
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
		std::lock_guard<std::mutex> lock(m_Mutex);

		std::queue<std::string>* MessageQueue = GetQueueOfType(Type);
	
		if (MessageQueue == nullptr || MessageQueue->empty())
		{
			//The queue is empty
			return "";
		}
		
		std::string Message = MessageQueue->front(); //Retrieve message
		MessageQueue->pop(); //Pop the message so that it is no longer in the queue
		m_MessageCount--;
		return Message;
	}

	bool Logger::AddMessage(const std::string& Message, LogType Type)
	{
		//This makes the function thread-safe by elimitating race conditions
		std::lock_guard<std::mutex> lock(m_Mutex);

		//Message length check
		if (Message.size() > m_MaxMessageSize)
		{
			return false;
		}

		std::queue<std::string>* MessageQueue = GetQueueOfType(Type);

		if (MessageQueue == nullptr)
		{
			return false;
		}

		//Check if the message count is already at its max value
		if (m_MessageCount > m_MaxMessages)
		{
			return false;
		}

		MessageQueue->push(Message);

		m_MessageCount++;
		return true;
	}

	LogType Logger::HasPendingMessage()
	{
		if (!m_ErrorMessages.empty())
			return LogType::Error;

		else if (!m_WarningMessages.empty())
			return LogType::Warning;

		else if (!m_NoteMessages.empty())
			return LogType::Note;

		else if (!m_SuccessMessages.empty())
			return LogType::Success;

		else
			return LogType::None;
	}
}