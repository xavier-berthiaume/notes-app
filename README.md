# Quick Notes

Quick Notes is a lightweight note-taking application built in C++ using the Qt framework. It allows users to write notes, view them, edit their contents, and delete them when no longer needed. The application is designed with simplicity and ease of use in mind, providing a clean and intuitive interface for managing personal notes.

## Features

- **Add Notes**: Create new notes with a title and body.
- **View Notes**: Display the details of selected notes, including the full title and body.
- **Edit Notes**: Modify the title and body of existing notes.
- **Delete Notes**: Remove notes you no longer need.
- **Dynamic Updates**: The application reflects changes in real-time, keeping the interface synchronized with your actions.
- **Truncated Titles**: Titles that are too long to fit in the designated area are automatically truncated with ellipses (e.g., "A very long title...").

## Getting Started

### Prerequisites

To build and run Quick Notes, you need:

- **Qt Framework**: Version 5 or later (Qt 6 recommended for best performance).
- **CMake**: Version 3.5 or later.
- **C++ Compiler**: Supporting C++17 or later.

### Building the Application

1. Clone the repository:
   ```bash
   git clone https://github.com/xavier-berthiaume/notes-app
   cd notes-app
   ```

2. Create a build directory and navigate to it:
   ```bash
   mkdir build
   cd build
   ```

3. Run CMake to configure the project:
   ```bash
   cmake ..
   ```

4. Build the application:
   ```bash
   make
   ```

5. Run the application:
   ```bash
   ./quick-notes
   ```

## Usage

1. **Adding a Note**:
   - Click the "Add Note" button.
   - Enter a title and body in the dialog that appears.
   - Click "Save" to add the note to the list.

2. **Viewing a Note**:
   - Select a note from the list. Its details will appear in the display area, showing the title and body.

3. **Editing a Note**:
   - Select a note and click the "Edit" button.
   - Modify the title and body in the dialog.
   - Click "Save" to apply the changes.

4. **Deleting a Note**:
   - Select a note and click the "Delete" button to remove it from the list.

## File Structure

- `main.cpp`: Entry point of the application.
- `mainwindow.*`: Implements the main user interface and application logic.
- `notemodel.*`: Defines a custom `QAbstractListModel` to manage notes.
- `note.*`: Defines the `Note` structure for storing note data.
- `creditwidget.*`: A custom dialog widget crediting me.
- `createnotedialog.*`: A custom dialog widget used to create and edit notes.

## Customization

- Modify the `NoteModel` class to change how notes are managed internally.
- Update the UI forms (`mainwindow.ui` and `creditwidget.ui`) using Qt Designer for a custom look and feel.

## Contributions

Contributions are welcome! If you have ideas for new features, feel free to open an issue or submit a pull request.

## License

This project is licensed under the GPL (GNU General Public License). See the `LICENSE` file for details.

---

Enjoy using Quick Notes to keep your ideas organized and easily accessible!

