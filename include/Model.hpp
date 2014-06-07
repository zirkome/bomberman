#ifndef _MODEL_H_
# define _MODEL_H_

# include <string>
# include <stdexcept>
# include <Model.hh>

# include "Model.hpp"
# include "AObject.hpp"
# include "AResource.hpp"

class Model : public AObject, public gdl::Model, public AResource//<Model>
{
public:
  Model(const std::string &path);
  virtual ~Model() {};

  virtual void	draw(gdl::AShader *shader, const gdl::Clock& clock);
};

#endif /* _MODEL_H_ */
