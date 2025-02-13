#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "ShaderProgram.h"
#include "TextureCache.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace T5 {
	const String tutorialLink = "learnopengl.com/Getting-started/Coordinate-Systems";
	const String vertexFilename = "vertexT5.h";
	const String fragmentFileName = "fragmentT5.h";


	struct UniformsTutorial5
	{
		UniformsTutorial5(OpenGLContext& openGLContext, OpenGLShaderProgram& shader)
		{
			model = createUniform(openGLContext, shader, "model");
			view = createUniform(openGLContext, shader, "view");
			projection = createUniform(openGLContext, shader, "projection");
			ourTextureBox = createUniform(openGLContext, shader, "ourTextureBox");
			ourTextureFace = createUniform(openGLContext, shader, "ourTextureFace");
		}

		ScopedPointer<OpenGLShaderProgram::Uniform>  model{ nullptr }, view{ nullptr }, projection{ nullptr }, ourTextureBox{ nullptr }, ourTextureFace{ nullptr };


	private:
		static OpenGLShaderProgram::Uniform* createUniform(OpenGLContext& openGLContext,
			OpenGLShaderProgram& shader,
			const char* uniformName)
		{
			if (openGLContext.extensions.glGetUniformLocation(shader.getProgramID(), uniformName) < 0)
				return nullptr;

			return new OpenGLShaderProgram::Uniform(shader, uniformName);
		}
	};

#pragma pack(1)
	struct VertexTutorial5 {
		struct Position {
			float x;
			float y;
			float z;
		};

		struct UV {
			float u;
			float v;
		};
		Position position;

		UV uv;

		VertexTutorial5(float x, float y, float z, float u, float v)
		{
			position.x = x;
			position.y = y;
			position.z = z;

			uv.u = u;
			uv.v = v;
		}
	};
#pragma pack()

	class SpriteTutorial5
	{
	public:
		SpriteTutorial5(OpenGLContext& openGLContext, bool& useUniform) :VBO(0), VAO(0),
			_openGLContext(openGLContext),
			_useUniform(useUniform)
		{
		}


		~SpriteTutorial5()
		{
			_openGLContext.extensions.glDeleteVertexArrays(1, &VAO);
			_openGLContext.extensions.glDeleteBuffers(1, &VBO);

		}



		void init(String BoxPath, String awsomeFacePath)
		{
			_pTextureBox = TextureCache::getTexture(BoxPath);
			_pTextureFace = TextureCache::getTexture(awsomeFacePath);

			if (!_pTextureBox || !_pTextureFace)
			{
				return;
			}

			_openGLContext.extensions.glGenVertexArrays(1, &VAO);
			_openGLContext.extensions.glGenBuffers(1, &VBO);



			VertexTutorial5 vertices[] = {
				{-0.5f, -0.5f, -0.5f,  0.0f, 0.0f},
				{ 0.5f, -0.5f, -0.5f,  1.0f, 0.0f},
				{ 0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
				{ 0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
				{-0.5f,  0.5f, -0.5f,  0.0f, 1.0f},
				{-0.5f, -0.5f, -0.5f,  0.0f, 0.0f},

				{-0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
				{ 0.5f, -0.5f,  0.5f,  1.0f, 0.0f},
				{ 0.5f,  0.5f,  0.5f,  1.0f, 1.0f},
				{ 0.5f,  0.5f,  0.5f,  1.0f, 1.0f},
				{-0.5f,  0.5f,  0.5f,  0.0f, 1.0f},
				{-0.5f, -0.5f,  0.5f,  0.0f, 0.0f},

				{-0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
				{-0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
				{-0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
				{-0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
				{-0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
				{-0.5f,  0.5f,  0.5f,  1.0f, 0.0f},

				{ 0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
				{ 0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
				{ 0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
				{ 0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
				{ 0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
				{ 0.5f,  0.5f,  0.5f,  1.0f, 0.0f},

				{-0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
				{ 0.5f, -0.5f, -0.5f,  1.0f, 1.0f},
				{ 0.5f, -0.5f,  0.5f,  1.0f, 0.0f},
				{ 0.5f, -0.5f,  0.5f,  1.0f, 0.0f},
				{-0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
				{-0.5f, -0.5f, -0.5f,  0.0f, 1.0f},

				{-0.5f,  0.5f, -0.5f,  0.0f, 1.0f},
				{ 0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
				{ 0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
				{ 0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
				{-0.5f,  0.5f,  0.5f,  0.0f, 0.0f},
				{-0.5f,  0.5f, -0.5f,  0.0f, 1.0f}
			};

			_openGLContext.extensions.glBindVertexArray(VAO);

			_openGLContext.extensions.glBindBuffer(GL_ARRAY_BUFFER, VBO);
			_openGLContext.extensions.glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


			// position attribute
			_openGLContext.extensions.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexTutorial5), (GLvoid*)offsetof(VertexTutorial5, position));
			_openGLContext.extensions.glEnableVertexAttribArray(0);


			_openGLContext.extensions.glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexTutorial5), (GLvoid*)offsetof(VertexTutorial5, uv));
			_openGLContext.extensions.glEnableVertexAttribArray(1);



			_openGLContext.extensions.glBindBuffer(GL_ARRAY_BUFFER, 0);
			_openGLContext.extensions.glBindVertexArray(0);
		}

		void setUniformEnv(OpenGLContext& ogc, OpenGLShaderProgram *shader)
		{
			_uniforms.reset(new UniformsTutorial5(ogc, *shader));
		}

		void draw()
		{
			_openGLContext.extensions.glActiveTexture(GL_TEXTURE0);
			if (_pTextureBox)
				_pTextureBox->bind();
			else return;

			_openGLContext.extensions.glActiveTexture(GL_TEXTURE1);
			if (_pTextureFace)
				_pTextureFace->bind();
			else return;

			if (_uniforms->ourTextureBox)
				_uniforms->ourTextureBox->set(0);
			if (_uniforms->ourTextureFace)
				_uniforms->ourTextureFace->set(1);


			_openGLContext.extensions.glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

			for (unsigned int i = 0; i < 10; i++)
			{
				if (_uniforms->model)
				{
					static float x = 0.;
					x += 0.0001;

					glm::mat4 model = glm::mat4(1.0f);
					model = glm::translate(model, cubePositions[i]);
					float angle = 20.0f * i;

					if (i % 3 == 0)
						model = glm::rotate(model, x + glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
					else
						model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

					_uniforms->model->setMatrix4(glm::value_ptr(model), 1, GL_FALSE);
				}

				if (_uniforms->view)
				{
					glm::mat4 view = glm::mat4(1.0f);
					// note that we're translating the scene in the reverse direction of where we want to move
					view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
					_uniforms->view->setMatrix4(glm::value_ptr(view), 1, GL_FALSE);
				}

				if (_uniforms->projection)
				{
					glm::mat4 projection;
					projection = glm::perspective(glm::radians(_angleValue), _screenWidth / _screenHeight, _zValue, 100.0f);
					_uniforms->projection->setMatrix4(glm::value_ptr(projection), 1, GL_FALSE);
				}

				glDrawArrays(GL_TRIANGLES, 0, 36);
			}

			return;
		}
		void setScreenWidthAndHeight(float w, float h)
		{
			_screenWidth = w;
			_screenHeight = h;
		}

		void setZValue(float z)
		{
			_zValue = z;
		}

		void setAngleValue(float angle)
		{
			_angleValue = angle;
		}
	public:

		glm::vec3 cubePositions[10]{
				  glm::vec3(0.0f,  0.0f,  0.0f),
				  glm::vec3(2.0f,  5.0f, -15.0f),
				  glm::vec3(-1.5f, -2.2f, -2.5f),
				  glm::vec3(-3.8f, -2.0f, -12.3f),
				  glm::vec3(2.4f, -0.4f, -3.5f),
				  glm::vec3(-1.7f,  3.0f, -7.5f),
				  glm::vec3(1.3f, -2.0f, -2.5f),
				  glm::vec3(1.5f,  2.0f, -2.5f),
				  glm::vec3(1.5f,  0.2f, -1.5f),
				  glm::vec3(-1.3f,  1.0f, -1.5f)
		};;
		float _screenWidth{ 1200.f };
		float _screenHeight{ 800.f };
		float _zValue;
		float _angleValue;
		GLuint VBO, VAO;

		OpenGLContext& _openGLContext;

		bool& _useUniform;
		OpenGLTexture* _pTextureBox{ nullptr }, *_pTextureFace{ nullptr };

		std::unique_ptr<UniformsTutorial5> _uniforms;

	};




	class Tutorial5 : public OpenGLAppComponent,
		public Button::Listener,
		public Slider::Listener
	{
	public:
		//==============================================================================
		Tutorial5() : _sprite(openGLContext, _useUniform)
		{
			openGLContext.setOpenGLVersionRequired(juce::OpenGLContext::openGL3_2);
			openGLContext.setComponentPaintingEnabled(true);

			_lblCompileInfo.reset(new Label("compileInfo", "Shader source build info."));
			addAndMakeVisible(_lblCompileInfo.get());


			_useUniformToggleButton.reset(new ToggleButton("Use Uniform"));
			addAndMakeVisible(_useUniformToggleButton.get());
			_useUniformToggleButton->addListener(this);

			_sliderAngle.reset(new Slider("_sliderAngle"));
			addAndMakeVisible(_sliderAngle.get());
			_sliderAngle->setRange(0, 180, 0);
			_sliderAngle->setSliderStyle(Slider::LinearHorizontal);
			_sliderAngle->setTextBoxStyle(Slider::TextBoxLeft, false, 80, 20);
			_sliderAngle->addListener(this);
			_sliderAngle->setValue(45.f);

			_sliderZ.reset(new Slider("_sliderZ"));
			addAndMakeVisible(_sliderZ.get());
			_sliderZ->setRange(0, 110, 0);
			_sliderZ->setSliderStyle(Slider::LinearHorizontal);
			_sliderZ->setTextBoxStyle(Slider::TextBoxLeft, false, 80, 20);
			_sliderZ->addListener(this);
			_sliderZ->setValue(0.1);


			addAndMakeVisible(_lblAngle);
			_lblAngle.setText("Angle:", dontSendNotification);
			_lblAngle.attachToComponent(_sliderAngle.get(), true);

			addAndMakeVisible(_lblZ);
			_lblZ.setText("Z Value:", dontSendNotification);
			_lblZ.attachToComponent(_sliderZ.get(), true);


			setSize(800, 600);
		}
		~Tutorial5()
		{
			shutdownOpenGL();
		}

		//==============================================================================
		void initialise() override
		{
			File f = File::getCurrentWorkingDirectory();
			macPath(f);
			auto vertexFile = f.getParentDirectory().getParentDirectory().getChildFile("Source").getChildFile("Shader").getChildFile(vertexFilename);
			auto fragmentFile = f.getParentDirectory().getParentDirectory().getChildFile("Source").getChildFile("Shader").getChildFile(fragmentFileName);
			_shaderProgram.reset(new ShaderProgram(openGLContext, vertexFile.getFullPathName(), fragmentFile.getFullPathName()));

			auto textureBoxFile = f.getParentDirectory().getParentDirectory().getChildFile("Resource").getChildFile("container.jpg").getFullPathName();
			auto textureAwsomeFace = f.getParentDirectory().getParentDirectory().getChildFile("Resource").getChildFile("awesomeface.png").getFullPathName();

			_sprite.init(textureBoxFile, textureAwsomeFace);
		}
		void shutdown() override
		{
			_shaderProgram->stopThread(1000);
			_shaderProgram.reset();
			TextureCache::clear();
		}
		void render() override
		{
			if (!OpenGLHelpers::isContextActive())
				return;
			auto res = _shaderProgram->updateShader();
			if (res >= 0)
			{
				if (res == 1)
				{
					_sprite.setUniformEnv(openGLContext, _shaderProgram->_shader);
				}

				const MessageManagerLock mmLock;
				if (mmLock.lockWasGained())
				{
					_lblCompileInfo->setText(_shaderProgram->getCompileResult() + " \n" + tutorialLink, NotificationType::dontSendNotification);
				}
			}

			OpenGLHelpers::clear(juce::Colour(0.2f, 0.3f, 0.3f, 1.0f));
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glEnable(GL_DEPTH_TEST);


			if (_shaderProgram->_shader)
			{
				_shaderProgram->_shader->use();

				_sprite.draw();
			}
		}

		//==============================================================================
		void paint(Graphics& g) override
		{

		}
		void resized() override
		{
			auto r = getLocalBounds();
			if (_lblCompileInfo)
			{
				_lblCompileInfo->setBounds(r.removeFromTop(proportionOfHeight(0.05000f)));
			}

			auto areaToggle = r.removeFromRight(proportionOfWidth(0.5));

			//_useUniformToggleButton->setBounds(areaToggle.removeFromTop(proportionOfHeight(0.05)));
			_sliderAngle->setBounds(areaToggle.removeFromTop(proportionOfHeight(0.05)));
			_sliderZ->setBounds(areaToggle.removeFromTop(proportionOfHeight(0.05)));


			_sprite.setScreenWidthAndHeight(getBounds().getWidth(), getBounds().getHeight());
		}

		void buttonClicked(Button* buttonThatWasClicked)
		{

			if (buttonThatWasClicked == _useUniformToggleButton.get())
			{
				_useUniform = _useUniformToggleButton->getToggleState();
			}

			//[UserbuttonClicked_Post]
			//[/UserbuttonClicked_Post]
		}

		void sliderValueChanged(Slider* sliderThatWasMoved) override
		{
			if (sliderThatWasMoved == _sliderAngle.get())
			{
				_sprite.setAngleValue(_sliderAngle->getValue());
			}
			else if (sliderThatWasMoved == _sliderZ.get())
			{
				_sprite.setZValue(_sliderZ->getValue());
			}
		}


	private:
		//==============================================================================
		// Your private member variables go here...

		SpriteTutorial5 _sprite;
		std::unique_ptr<ShaderProgram> _shaderProgram;
		std::unique_ptr<Label> _lblCompileInfo{ nullptr };
		bool init{ false };

		bool _useUniform{ false };
		bool _useAttribute{ false };

		std::unique_ptr<ToggleButton> _useUniformToggleButton;

		std::unique_ptr<Slider> _sliderAngle;
		std::unique_ptr<Slider> _sliderZ;

		Label _lblAngle;

		Label _lblZ;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Tutorial5)
	};
}