#pragma once
using namespace king::worksample;

static const std::string assetDir = SAMPLE_ASSETS_DIR;
static const std::string textureDir = assetDir + "textures/";
static const std::string fontDir = assetDir + "fonts/";

struct sample : public game {
	sample(window& renderWindow)
		: mGreen(textureDir + "gem_green.png")
		, mYellow(textureDir + "gem_yellow.png")
		, mPurple(textureDir + "gem_purple.png")
		, mBlue(textureDir + "gem_blue.png")
		, mRed(textureDir + "gem_red.png")
		, mRotateText("This element rotates!", fontDir + "Roboto-Bold.ttf")
		, mMoveText("Click to move this gem!", fontDir + "Roboto-Bold.ttf")
		, mMouse(renderWindow) {
		mBlue.setPosition(100, 100);
		mGreen.setPosition(650, 100);
		mYellow.setPosition(100, 490);
		mPurple.setPosition(650, 490);
		mRed.setPosition(400, 500);
		mRed.setOrigin(mRed.getLocalBounds().width / 2, mRed.getLocalBounds().height / 2);
		mMoveText.setCharacterSize(16);
		mMoveText.setOrigin(mMoveText.getLocalBounds().width / 2, mMoveText.getLocalBounds().height / 2);
		mMoveText.setPosition(400, 540);
		mRotateText.setOrigin(mRotateText.getLocalBounds().width / 2,
							  mRotateText.getLocalBounds().height / 2);
		mRotateText.setPosition(400, 300);
	}

	virtual void update(float deltaTime) override {
		mRotateText.setRotation(mRotateText.getRotation() + deltaTime * 60);

		if (mMouse.isButtonDown()) {
			mRed.setPosition(mMouse.getPosition());
			mMoveText.setPosition(mMouse.getPositionX(), mMouse.getPositionY() + 40.f);
		}
	}

	virtual void render(window& renderTarget) override {
		renderTarget.draw(mGreen);
		renderTarget.draw(mYellow);
		renderTarget.draw(mPurple);
		renderTarget.draw(mBlue);
		renderTarget.draw(mRed);
		renderTarget.draw(mMoveText);
		renderTarget.draw(mRotateText);
	}

	virtual bool isFinished() const override {
		return false;
	}

	sprite mGreen;
	sprite mYellow;
	sprite mPurple;
	sprite mBlue;
	sprite mRed;
	text mRotateText;
	text mMoveText;
	mouse mMouse;
};
