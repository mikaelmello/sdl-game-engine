#ifndef HELPERS_H
#define HELPERS_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <string>
#include <vector>

namespace Helpers {
    
// Divide uma string em um vetor de strings de acordo um caractere delimitador
// Criado por Evan Teran
// Disponível em: https://stackoverflow.com/questions/236129/most-elegant-way-to-split-a-string
template<typename Out>
void split(const std::string &s, char delim, Out result);

// Divide uma string em um vetor de strings de acordo um caractere delimitador
// Criado por Evan Teran
// Disponível em: https://stackoverflow.com/questions/236129/most-elegant-way-to-split-a-string
std::vector<std::string> split(const std::string &s, char delim);

std::vector<std::string> split(const std::string& text, const std::string& delims);

bool is_whitespace(const std::string& s);

float rad_to_deg(float rad);

} // end namespace Helpers

#endif
