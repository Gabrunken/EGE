#pragma once
#include <string>
#include <queue>
#include <mutex>

namespace EGE
{
	enum class LogType
	{
		None,
		Error,
		Warning,
		Note,
		Success
	};


	class Logger
	{
	public:
		/*
		*This function retrieves the first message of type "Type" in the EGE message stack,
		*meaning the oldest message.
		*It reads and pops the message from the stack, so that after this call it is no longer
		*retrievable.
		*Returns a null string if there was no message, or if an error occurred.
		*/
		static std::string GetFirstMessage(LogType Type);

		/*
		*Adds a message pushing it onto the EGE message stack of type "Type".
		*Returns false if anything went wrong (i.e. message too big).
		*/
		static bool AddMessage(const std::string& Message, LogType Type);

		/*
		*Used to check if there are any pending messages.
		*If there are any, this function returns the LogType of the message
		*it found in this order of relevance: Error, Warning, Note, Success, so it's good
		*to put this function in a loop.
		*Returns LogType::None if no messages are found.
		*/
		static LogType HasPendingMessage();

	private:
		//A mutex is used to prevent race conditions on Retrieving and Adding
		static std::mutex m_Mutex;

		//This are the various message stacks
		static std::queue<std::string> m_ErrorMessages;
		static std::queue<std::string> m_WarningMessages;
		static std::queue<std::string> m_NoteMessages;
		static std::queue<std::string> m_SuccessMessages;

		//The maximum number of messages summed in the various stacks.
		//If you Add a message and you didn't retrieve for the last "MaxMessages" messages,
		//the one you are trying to add will be ignored.
		static constexpr size_t m_MaxMessages = 100;

		//The maximum number of characters that can be contained in a message.
		static constexpr size_t m_MaxMessageSize = 512;

		//The total message count
		static size_t m_MessageCount;

		static std::queue<std::string>* GetQueueOfType(LogType Type);
	};
}