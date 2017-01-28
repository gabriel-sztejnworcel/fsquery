
#include "Shell.h"

#include "CMemGuard.h"

#include <readline/readline.h>
#include <readline/history.h>

#include <iostream>

Shell::Shell() :
	m_prompt("shell> "),
	m_defaultAction(nullptr),
	m_stop(false)
{
	
}

Shell::~Shell()
{
	
}

void Shell::Run()
{
	m_stop = false;
	
	while (!m_stop)
	{
		CMemGuard<char> cmdPtr(readline(m_prompt.c_str()));
		
		if (cmdPtr.Get()[0] != 0)
		{
			add_history(cmdPtr.Get());
			std::string cmd(cmdPtr.Get());
			ProcessCommand(cmd);
		}
	}
}

void Shell::SetPrompt(const std::string& prompt)
{
	m_prompt = prompt;
}

void Shell::RegisterCommandAction(const std::string& cmd, std::function<int(const std::string&)> action)
{
	m_commandActions[cmd] = action;
}

void Shell::RegisterDefaultAction(std::function<int(const std::string&)> action)
{
	m_defaultAction = action;
}

void Shell::SetStopCommand(const std::string& stopCmd)
{
	m_stopCmd = stopCmd;
}

int Shell::GetLastReturnVal() const
{
	return m_lastReturnVal;
}

void Shell::ProcessCommand(const std::string& cmd)
{
	if (cmd == m_stopCmd)
	{
		m_stop = true;
		m_lastReturnVal = 0;
		return;
	}
	
	std::string firstWord;
	size_t firstSpaceIndex = cmd.find_first_of(' ');
	
	if (firstSpaceIndex != std::string::npos)
	{
		size_t firstWordLen = firstSpaceIndex;
		firstWord = cmd.substr(0, firstWordLen);
	}
	else
	{
		firstWord = cmd;
	}
	
	auto iter = m_commandActions.find(firstWord);
	if (iter != m_commandActions.end())
	{
		m_lastReturnVal = (iter->second)(cmd);
	}
	else if (m_defaultAction != nullptr)
	{
		m_lastReturnVal = m_defaultAction(cmd);
	}
	else
	{
		std::cout << "Command '" + firstWord + "' not found" << std::endl;
		m_lastReturnVal = -1;
	}
}
