#ifndef _ARESOURCE_H_
# define _ARESOURCE_H_

# include <string>

class AResource
{
public:
  explicit AResource(const std::string& name);

  virtual ~AResource();

private:
  std::string _name;
};

#endif /* _IRESOURCE_H_ */
