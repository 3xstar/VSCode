# CostCount
Simple expense tracker built with Flutter.
# Description
Quickly log your expenses and see the total sum. No complex settings, no registration, no cloud — everything stays in app memory.

# Features
• Add entries: title + amount
• Input validation (numbers only for amount)
• Swipe-to-delete (no confirmation dialog)
• Auto-recalculating total sum
• Dark theme by default
• Empty state hint when no records exist

# Requirements
• Flutter SDK 3.0+
• Android / iOS / Web device or emulator

# Setup
1. Clone the repository
git clone <your-repo-url>

2. Navigate to project folder
cd CostCount

3. Install dependencies
flutter pub get

4. Run the app
flutter run

# Web Launch (if browser doesn't open automatically)
flutter run -d web-server
Then open the localhost URL from console in your browser manually

# Usage
Tap the + button in the bottom-right corner.
Enter expense title and amount.
Tap Save — the record appears in the list.
Swipe left on any item to delete it.
Check the total sum in the bottom bar.

# Notes
• Data is stored only in memory — it resets after app restart (no persistent storage).
• Amount field accepts decimal values (e.g., 199.99).
• App name in AppBar can be changed to any fun unique name you prefer.

# License
MIT — free for personal and commercial use.
