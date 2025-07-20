#include <sparse/sparse.h>
#include <ncurses.h>
#include <vector>

class ImageViewer {
public:
    void Load(const char* path) {
        // Parse sparse image
        SparseImage* img = sparse_image_parse(path);
        blocks_ = GetBlockMap(img);
    }

    void Run() {
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        
        while (true) {
            RenderUI();
            int ch = getch();
            if (ch == 'q') break;
            HandleInput(ch);
        }
        
        endscr();
    }

private:
    std::vector<BlockInfo> blocks_;

    void RenderUI() {
        clear();
        printw("Android Image Viewer v4.0 | %dx%d blocks\n", 
               blocks_.width, blocks_.height);
        
        for (const auto& block : blocks_) {
            attron(COLOR_PAIR(block.status));
            addch(block.visual_char);
            attroff(COLOR_PAIR(block.status));
        }
        
        refresh();
    }
};
