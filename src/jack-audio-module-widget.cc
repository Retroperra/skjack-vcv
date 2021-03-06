#include "jack-audio-module-widget.hh"
#include "jack-audio-module.hh"
#include "hashids.hh"
#include "components.hh"

namespace rack {
   extern std::shared_ptr<Font> gGuiFont;
}

struct JackPortLedTextField : public LedDisplayTextField {
   int managed_port;
   JackAudioModuleWidget* master;

   JackPortLedTextField() : LedDisplayTextField() {
      font = Font::load(assetPlugin(plugin, "res/3270Medium.ttf"));
   }

   void draw(NVGcontext *vg) override {
	nvgScissor(vg, 0, 0, box.size.x, box.size.y);

	NVGcolor fill = nvgRGB(20, 39, 53);
	NVGcolor color = nvgRGB(255, 255, 255);

	// Background
	nvgBeginPath(vg);
	nvgRoundedRect(vg, 0, 0, box.size.x, box.size.y, 5.0);
	nvgFillColor(vg, fill);
	nvgFill(vg);

	// Text
	if (font->handle >= 0) {
	   bndSetFont(font->handle);



	   NVGcolor highlightColor = color;
	   highlightColor.a = 0.5;

	   int begin = min(cursor, selection);
	   int end = (this == gFocusedWidget) ? max(cursor, selection) : -1;
	   bndIconLabelCaret(vg,
			     textOffset.x, textOffset.y,
			     box.size.x - 2*textOffset.x,
			     box.size.y - 2*textOffset.y,
			     -1,
			     color,
			     13, // font size
			     text.c_str(),
			     highlightColor,
			     begin, end);

	   bndSetFont(gGuiFont->handle);
	}

	nvgResetScissor(vg);
   }

   void onTextChange() override {
      LedDisplayTextField::onTextChange();
      master->on_port_renamed(managed_port, text);
   }
};

JackAudioModuleWidget::JackAudioModuleWidget(JackAudioModule *module) : ModuleWidget(module) {
	setPanel(SVG::load(assetPlugin(plugin, "res/JackAudioB.svg")));

	addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
	addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
	addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
	addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

	addInput(Port::create<DavidLTPort>(mm2px(Vec(3.7069211, 10.530807)), Port::INPUT, module, JackAudioModule::AUDIO_INPUT + 0));
	addInput(Port::create<DavidLTPort>(mm2px(Vec(3.7069211, 23.530807)), Port::INPUT, module, JackAudioModule::AUDIO_INPUT + 1));
	addInput(Port::create<DavidLTPort>(mm2px(Vec(3.7069211, 36.530807)), Port::INPUT, module, JackAudioModule::AUDIO_INPUT + 2));
	addInput(Port::create<DavidLTPort>(mm2px(Vec(3.7069211, 49.530807)), Port::INPUT, module, JackAudioModule::AUDIO_INPUT + 3));

	{
		port_names[0] = Widget::create<JackPortLedTextField>(mm2px(Vec(13.7069211, 8.530807)));
		auto self = reinterpret_cast<JackPortLedTextField*>(port_names[0]);
		self->managed_port = 0;
		self->master = this;
		self->box.size = mm2px(Vec(35.0, 10.753));
		addChild(self);
	}

	{
		port_names[1] = Widget::create<JackPortLedTextField>(mm2px(Vec(13.7069211, 21.530807)));
		auto self = reinterpret_cast<JackPortLedTextField*>(port_names[1]);
		self->managed_port = 1;
		self->master = this;
		self->box.size = mm2px(Vec(35.0, 10.753));
		addChild(self);
	}

	{
		port_names[2] = Widget::create<JackPortLedTextField>(mm2px(Vec(13.7069211, 34.530807)));
		auto self = reinterpret_cast<JackPortLedTextField*>(port_names[2]);
		self->managed_port = 2;
		self->master = this;
		self->box.size = mm2px(Vec(35.0, 10.753));
		addChild(self);
	}

	{
		port_names[3] = Widget::create<JackPortLedTextField>(mm2px(Vec(13.7069211, 47.530807)));
		auto self = reinterpret_cast<JackPortLedTextField*>(port_names[3]);
		self->managed_port = 3;
		self->master = this;
		self->box.size = mm2px(Vec(35.0, 10.753));
		addChild(self);
	}

	addOutput(Port::create<DavidLTPort>(mm2px(Vec(3.7069211, 62.143906)), Port::OUTPUT, module, JackAudioModule::AUDIO_OUTPUT + 0));
	addOutput(Port::create<DavidLTPort>(mm2px(Vec(3.7069211, 75.143906)), Port::OUTPUT, module, JackAudioModule::AUDIO_OUTPUT + 1));
	addOutput(Port::create<DavidLTPort>(mm2px(Vec(3.7069211, 88.143906)), Port::OUTPUT, module, JackAudioModule::AUDIO_OUTPUT + 2));
	addOutput(Port::create<DavidLTPort>(mm2px(Vec(3.7069211, 101.143906)), Port::OUTPUT, module, JackAudioModule::AUDIO_OUTPUT + 3));

	{
		port_names[4] = Widget::create<JackPortLedTextField>(mm2px(Vec(13.7069211, 60.530807)));
		auto self = reinterpret_cast<JackPortLedTextField*>(port_names[4]);
		self->managed_port = 4;
		self->master = this;
		self->box.size = mm2px(Vec(35.0, 10.753));
		addChild(self);
	}

	{
		port_names[5] = Widget::create<JackPortLedTextField>(mm2px(Vec(13.7069211, 73.530807)));
		auto self = reinterpret_cast<JackPortLedTextField*>(port_names[5]);
		self->managed_port = 5;
		self->master = this;
		self->box.size = mm2px(Vec(35.0, 10.753));
		addChild(self);
	}

	{
		port_names[6] = Widget::create<JackPortLedTextField>(mm2px(Vec(13.7069211, 86.530807)));
		auto self = reinterpret_cast<JackPortLedTextField*>(port_names[6]);
		self->managed_port = 6;
		self->master = this;
		self->box.size = mm2px(Vec(35.0, 10.753));
		addChild(self);
	}

	{
		port_names[7] = Widget::create<JackPortLedTextField>(mm2px(Vec(13.7069211, 99.530807)));
		auto self = reinterpret_cast<JackPortLedTextField*>(port_names[7]);
		self->managed_port = 7;
		self->master = this;
		self->box.size = mm2px(Vec(35.0, 10.753));
		addChild(self);
	}

	char port_name[128];
	hashidsxx::Hashids hash("grilled cheese sandwiches");
	std::string id = hash.encode(reinterpret_cast<size_t>(module));

	for (int i = 0; i < JACK_PORTS; i++) {
	  snprintf(reinterpret_cast<char*>(&port_name), 128, "%s:%d", id.c_str(), i);
	  // XXX using setText here would cause crashes because it would try to tell
	  port_names[i]->text = std::string(port_name);
	}
}

JackAudioModuleWidget::~JackAudioModuleWidget() {
}

json_t* JackAudioModuleWidget::toJson() {
	auto map = ModuleWidget::toJson();
	auto port_names = json_array();

	for (int i = 0; i < JACK_PORTS; i++) {
		auto str = json_string(this->port_names[i]->text.c_str());
		json_array_append_new(port_names, str);
	}

	json_object_set_new(map, "port_names", port_names);
	return map;
}

void JackAudioModuleWidget::fromJson(json_t* json) {
	auto port_names = json_object_get(json, "port_names");
	if (json_is_array(port_names)) {
		for (size_t i = 0; i < std::min(json_array_size(port_names), (size_t)8); i++) {
			auto item = json_array_get(port_names, i);
			if (json_is_string(item)) {
				this->port_names[i]->setText(std::string(json_string_value(item), json_string_length(item)));
			}
		}
	}
}

void JackAudioModuleWidget::on_port_renamed(int port, const std::string& name) {
	if (port < 0 || port > JACK_PORTS) return;
	if (!g_jack_client.alive()) return;
	auto module = reinterpret_cast<JackAudioModule*>(this->module);
	if (!module) return;

	// XXX port names must be unique per client; using a non-unique name here
	// doesn't appear to "fail" but you do get a port with a blank name.
	if (!module->jport[port].rename(name)) {
		debug("Changing port name failed");
		//port_names[port]->setText(std::string(jack_port_short_name(module->jport[port])));
	}
}

// Specify the Module and ModuleWidget subclass, human-readable
// author name for categorization per plugin, module slug (should never
// change), human-readable module name, and any number of tags
// (found in `include/tags.hpp`) separated by commas.
Model *jack_audio_module = Model::create<JackAudioModule, JackAudioModuleWidget>("SkJack", "JackAudio", "JACK Audio", EXTERNAL_TAG);
