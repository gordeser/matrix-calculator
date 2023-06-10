//
// Created by gordeser on 15.05.2023.
//

#include "MatrixCalculator.h"
#include "Exceptions/ExporterException.h"
#include "Exceptions/MatrixException.h"
#include "Exceptions/OperationException.h"
#include "Exceptions/ParserException.h"
#include "Exceptions/StorageException.h"

void MatrixCalculator::runApplication() {
    showGreeting();
    while (true) {
        m_console.showText("\n");
        m_console.showText("$ ");
        std::string input = m_console.getInput();

        if (input == "quit" || input == "exit")
            break;

        try {
            m_parser.parseInput(input);
        } catch (ExporterException &e) {
            m_console.showText(e.what());
        } catch (MatrixException &e) {
            m_console.showText(e.what());
        } catch (OperationException &e) {
            m_console.showText(e.what());
        } catch (ParserException &e) {
            m_console.showText(e.what());
        } catch (StorageException &e) {
            m_console.showText(e.what());
        }
    }
    showFarewall();
}

void MatrixCalculator::showGreeting() const {
    m_console.showText("Hello!\n");
    m_console.showText("Available commands you can get using \"help\"\n");
}

void MatrixCalculator::showFarewall() const {
    m_console.showText("Goodbye!\n");
}