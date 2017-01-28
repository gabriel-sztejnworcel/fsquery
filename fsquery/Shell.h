
#ifndef SHELL_H
#define SHELL_H

#include <string>
#include <functional>
#include <unordered_map>

class Shell
{
public:
	Shell();
	~Shell();
	
	void Run();
	
	void SetPrompt(const std::string& prompt);
	void RegisterCommandAction(const std::string& cmd, std::function<int(const std::string&)> action);
	void RegisterDefaultAction(std::function<int(const std::string&)> action);
	void SetStopCommand(const std::string& stopCmd);
	
protected:
	int GetLastReturnVal() const;
	
private:
	void ProcessCommand(const std::string& cmd);

	bool m_stop;
	std::string m_prompt;
	int m_lastReturnVal;
	std::unordered_map<std::string, std::function<int(const std::string&)>> m_commandActions;
	std::function<int(const std::string&)> m_defaultAction;
	std::string m_stopCmd;
};

#endif // SHELL_H
