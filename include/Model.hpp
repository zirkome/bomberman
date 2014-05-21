#ifndef _MODEL_H_
#define _MODEL_H_

# include <string>
# include <Model.hh>
# include "AObject.hpp"

class Model : public AObject, public gdl::Model
{
private:
  std::string	_path;
public:
  Model(const std::string &);
  virtual ~Model() {};
  virtual bool	initialize();

  virtual void	draw(gdl::AShader *shader, const gdl::Clock& clock);
};

#endif /* _MODEL_H_ */
