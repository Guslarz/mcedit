#include "MceditBackend.h"



MceditBackend::MceditBackend(BaseTool *const tool) :
	BaseBackend(tool),
	isOpen(true),
	terminal(),
	input(),
	menu(terminal.getMenuWindow(), terminal.getToolWindow()),
	normalMode(input, *tool, menu, editionHandler),
	tooSmallMode(input),
	helpMode(input, bindsCollection),
	alertMode(input),
	paramMode(input, *tool),
	currentMode(&normalMode)
{
	tool->assignWindow(terminal.getToolWindow());
}


MceditBackend::~MceditBackend()
{}


void MceditBackend::bind(const std::string &command, std::function<void()> handler, const std::string &description)
{
	auto toBind = Bind(command, handler, description);
	try {
		auto parsed = toBind.getParsed();
		menu.addItem(parsed, handler);
		bindsCollection.push_back(toBind);
	}
	catch (ParsedBind::Edition&) {
		editionHandler = handler;
		bindsCollection.push_back(toBind);
	}
	catch (ParsedBind::Invalid&) {}
}


void MceditBackend::start()
{
	bind(".File.Help", [this]() { this->helpHandler(); }, "");
	bind(".File.Quit", [this]() { this->quitHandler(); }, "");
	menu.setPosition();
	menu.renderTop();
	while (isOpen) {
		try {
			(*currentMode)();
		}
		catch (const OptionItem *item) {
			paramMode.setTarget(item);
			currentMode = &paramMode;
		}
		catch (Mode::Resize&) {
			handleResize();
		}
		catch (Mode::End&) {
			handleModeEnd();
		}
	}
}


void MceditBackend::handleResize()
{
	terminal.resize();
	try {
		menu.setPosition();
		menu.renderTop();
		currentMode = &normalMode;
		tool->assignWindow(terminal.getToolWindow());
		tool->setEntry("KEY", "<RESIZE>");
		if (editionHandler)
			editionHandler();
	}
	catch (Menu::TooSmallTerminal&) {
		currentMode = &tooSmallMode;
	}
}


void MceditBackend::handleModeEnd()
{
	terminal.restore();
	currentMode = &normalMode;
}


void MceditBackend::helpHandler()
{
	currentMode = &helpMode;
}


void MceditBackend::quitHandler()
{
	try {
		std::string entry = tool->getEntry("IS_SAVED");
		if (entry == "NO") {
			alertMode.setMessage(unsavedAlert);
			currentMode = &alertMode;
			return;
		}
	}
	catch (BaseTool::UndefinedEntry&) {}

	isOpen = false;
}


const std::string MceditBackend::unsavedAlert = "Can't close unsaved file!";
