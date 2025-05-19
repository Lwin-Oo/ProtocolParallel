// 🍎 macOS-specific header for accessing currently active (frontmost) applications
#import <AppKit/AppKit.h> // Provides macOS GUI and app management APIs

// 🧱 Standard C++ libraries
#include <iostream>      // For console I/O
#include <unordered_map> // For storing app sessions with app name as key
#include <string>        // For using std::string
#include <chrono>        // For time tracking
#include <thread>        // For sleep and concurrent execution
#include <mutex>         // For thread-safe access (critical sections)
#include <vector>        // To store multiple session durations
#include <algorithm>     // For possible future enhancements
#include <numeric>       // For reducing data, e.g., average focus time
#include <iomanip>       // For formatting output (precision)
#include <fstream>       // For writing logs to file
#include <ctime>         // For getting current date/time

// ⏱ Aliases for cleaner chrono usage
using Clock = std::chrono::system_clock;
using Seconds = std::chrono::seconds;

// 🗃️ Structure to hold session data for each app
struct AppSession {
    std::string appName;                 // Name of the application
    Clock::time_point startTime;         // Start time of the current session
    Seconds totalDuration = Seconds(0);  // Total accumulated time used
    std::vector<Seconds> focusDurations; // Stores individual focus durations (time between switches)
};

// 🔐 Mutex to synchronize access to session data across threads
std::mutex sessionMutex;

// 🍏 Gets the name of the current frontmost application (macOS only)
std::string getFrontmostApp() {
    NSRunningApplication* frontmost = [[NSWorkspace sharedWorkspace] frontmostApplication];
    NSString* name = [frontmost localizedName];
    return std::string([name UTF8String]); // Convert NSString to std::string
}

// 📅 Returns current date as a string in YYYY-MM-DD format
std::string getCurrentDateString() {
    std::time_t now = std::time(nullptr);     // Get current system time
    char buf[11];                             // Buffer to hold date string
    std::strftime(buf, sizeof(buf), "%Y-%m-%d", std::localtime(&now));
    return std::string(buf);
}

// 💾 Writes daily usage log to a file with the current date in its filename
void writeDailyLog(const std::unordered_map<std::string, AppSession>& sessions) {
    std::string filename = "lunr_log_" + getCurrentDateString() + ".log";
    std::ofstream file(filename); // Create and open file

    file << "📅 Date: " << getCurrentDateString() << "\n";
    for (const auto& [app, session] : sessions) {
        int mins = session.totalDuration.count() / 60;
        int secs = session.totalDuration.count() % 60;
        file << app << "," << mins << "m " << secs << "s\n"; // CSV-like format
    }

    file.close();
    std::cout << "\n📁 Log saved to " << filename << "\n";
}

// 📊 Prints usage summary in terminal
void printSummary(const std::unordered_map<std::string, AppSession>& sessions) {
    std::cout << "\n✨ Daily App Usage Summary:\n";
    for (const auto& [app, session] : sessions) {
        int mins = session.totalDuration.count() / 60;
        int secs = session.totalDuration.count() % 60;
        std::cout << " - " << std::setw(20) << std::left << app
                  << ": " << mins << "m " << secs << "s\n";
    }
}

// 🧠 Analyzes user behavior from app usage (called every 30 seconds)
void analyzeBehavior(const std::unordered_map<std::string, AppSession>& sessions) {
    std::cout << "\n🧠 [Analyzer] Behavior Snapshot:\n";

    int totalSwitches = 0;
    Seconds totalFocusTime(0);
    std::string topApp;
    int maxDuration = 0;

    // Determine most used app, total time, number of switches
    for (const auto& [app, session] : sessions) {
        int duration = session.totalDuration.count();
        if (duration > maxDuration) {
            maxDuration = duration;
            topApp = app;
        }

        totalFocusTime += session.totalDuration;
        totalSwitches += session.focusDurations.size();
    }

    // Calculate average focus time per session switch
    double avgFocus = totalSwitches ? totalFocusTime.count() / static_cast<double>(totalSwitches) : 0;

    std::cout << " - Top App: " << topApp << " (" << maxDuration / 60 << "m " << maxDuration % 60 << "s)\n";
    std::cout << " - Total Switches: " << totalSwitches << "\n";
    std::cout << " - Avg. Focus Time: " << std::fixed << std::setprecision(2) << avgFocus << "s\n";
    std::cout << " - Fragmentation Index: " << (totalSwitches > 0 ? 100.0 / totalSwitches : 0) << "\n";
    std::cout << "----------------------------------------\n";
}

// 🔄 Background thread that runs behavior analysis every 30 seconds
void startBehaviorAnalyzer(const std::unordered_map<std::string, AppSession>* sharedSessions) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(30)); // Wait before analysis

        // Take a thread-safe snapshot of sessions
        std::unordered_map<std::string, AppSession> snapshot;
        {
            std::lock_guard<std::mutex> lock(sessionMutex);
            snapshot = *sharedSessions;
        }

        // Analyze and print the snapshot
        analyzeBehavior(snapshot);
    }
}

int main() {
    std::unordered_map<std::string, AppSession> sessions; // Track app sessions

    // Start tracking the current frontmost app
    std::string currentApp = getFrontmostApp();
    AppSession currentSession{currentApp, Clock::now()};

    std::cout << "[Lunr] App Usage Logging Started...\n";

    // 🚀 Launch the background analyzer thread
    std::thread analyzerThread(startBehaviorAnalyzer, &sessions);
    analyzerThread.detach(); // Run independently

    // 🔁 Main loop: check every 5 seconds for app changes
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(5)); // Sample every 5 seconds
        std::string frontApp = getFrontmostApp();

        // Detect app switch
        if (frontApp != currentApp) {
            auto now = Clock::now();
            Seconds duration = std::chrono::duration_cast<Seconds>(now - currentSession.startTime);

            {
                std::lock_guard<std::mutex> lock(sessionMutex);
                sessions[currentApp].appName = currentApp;
                sessions[currentApp].totalDuration += duration;
                sessions[currentApp].focusDurations.push_back(duration); // Save current session duration
            }

            // Start new session
            currentApp = frontApp;
            currentSession = AppSession{currentApp, now};
        }

        std::cout << "." << std::flush; // Visual heartbeat

        // Exit condition: if user presses Enter
        if (std::cin.peek() == '\n') break;
    }

    // 🔚 Final session tracking before exit
    auto now = Clock::now();
    Seconds duration = std::chrono::duration_cast<Seconds>(now - currentSession.startTime);
    {
        std::lock_guard<std::mutex> lock(sessionMutex);
        sessions[currentApp].appName = currentApp;
        sessions[currentApp].totalDuration += duration;
        sessions[currentApp].focusDurations.push_back(duration);
    }

    // 📊 Final summary and log file creation
    printSummary(sessions);
    writeDailyLog(sessions);

    return 0;
}
