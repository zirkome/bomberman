#ifndef _ARESOURCE_H_
# define _ARESOURCE_H_

class AResource;

#include <string>

//template <typename T>
class AResource
{
public:
  explicit AResource(const std::string& name);

  virtual ~AResource();

private:
	std::string _name;
};

#endif /* _IRESOURCE_H_ */
