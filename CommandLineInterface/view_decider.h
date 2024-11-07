#ifndef COMMAND_DECIDER_H
#define COMMAND_DECIDER_H

/**
 * @brief A class that takes in user input, and decides which user interface function (view) should be called.
 * This class is the direct abstraction between the cli, and the application views.
 */
class ViewDecider {
public:
    /**
     * @brief Decide which function to call based on the user command input
     * @example "add London" The command being "add"
     * 
     * @param input The input string that the user has typed
     */
    void decideView(const char* input);

private:
    /**
     * @brief check if there is a argument to the command, if empty or null
     * @example command <arg1> 
     * 
     * @param arg1 The argument
     * @return true if is valid
     */
    bool containsArg1(char* arg1);
    /**
     * @brief check if there is a second argument to the command, if empty or null
     * @example command <arg1> <arg2>
     * 
     * @param arg2 The argument
     * @return true if is valid
     */
    bool containsArg2(char* arg2);
};

#endif // COMMAND_DECIDER_H

