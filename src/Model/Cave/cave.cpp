#include "cave.h"

namespace s21 {
Cave::~Cave() { ClearData(); }

void Cave::SetRandomSize() { rows_ = cols_ = std::rand() % 48 + 2; }

void Cave::GeneratePerfect() {
    if (rows_ && cols_) {
        AllocateMemory();
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                matrix_of_cells_[i][j] = std::rand() % 2;
            }
        }
    }
}

bool Cave::ParseFile(std::string path) {
    std::fstream fs;
    fs.open(path, std::fstream::in);
    if (!fs.is_open()) return false;
    fs >> rows_;
    fs >> cols_;
    if (rows_ < min_width_ && rows_ > max_width_ && cols_ < min_width_ && cols_ > max_width_) {
        rows_ = cols_ = 0;
        return false;
    }
    AllocateMemory();
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            fs >> matrix_of_cells_[i][j];
        }
    }
    fs.close();
    return true;
}

void Cave::AllocateMemory() {
    matrix_of_cells_.resize(rows_);
    for (int i = 0; i < rows_; i++) {
        matrix_of_cells_[i].resize(cols_);
    }
}

void Cave::ClearData() { matrix_of_cells_.clear(); }

int Cave::GetRows() { return rows_; }

int Cave::GetCols() { return cols_; }

const AbstractClass::matrix& Cave::GetCaveMatrix() { return matrix_of_cells_; }

void Cave::SetRows(int rows) { rows_ = rows; }

void Cave::SetCols(int cols) { cols_ = cols; }


void Cave::NextStep(int birth_limit, int death_limit) {
    matrix tmp_matrix(matrix_of_cells_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            int upper = (i == 0) ? rows_ - 1 : i - 1;
            int lower = (i == rows_ - 1) ? 0 : i + 1;
            int left = (j == 0) ? cols_ - 1 : j - 1;
            int right = (j == cols_ - 1) ? 0 : j + 1;
            int sum = tmp_matrix[upper][left] + tmp_matrix[upper][j] + tmp_matrix[upper][right] +
                      tmp_matrix[i][left] + tmp_matrix[i][right] + tmp_matrix[lower][left] +
                      tmp_matrix[lower][j] + tmp_matrix[lower][right];
            if (tmp_matrix[i][j]) {
                if (sum < death_limit) matrix_of_cells_[i][j] = 0;
            } else {
                if (sum > birth_limit) matrix_of_cells_[i][j] = 1;
            }
        }
    }
}
}  // namespace s21
