#ifndef HELPER_HPP_
# define HELPER_HPP_

# include <string>
# include <vector>

# define MAX_DATE 13

void split(const std::string& str, const std::string& delim,
           std::vector<std::string>& parts);

std::string getDate();

#endif /* HELPER_HPP_ */
