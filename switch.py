import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import switch
from esphome.const import CONF_CHANNEL, CONF_ID
from . import M5STACK4RELAYComponent, m5stack_4relay_ns

DEPENDENCIES = ["m5stack_4relay"]

M5STACK4RELAYSwitch = m5stack_4relay_ns.class_("M5STACK4RELAYSwitch", switch.Switch)
CONF_M5STACK4RELAY_ID = "m5stacl_4relay_id"

CONFIG_SCHEMA = switch.SWITCH_SCHEMA.extend(
    {
        cv.Required(CONF_ID): cv.declare_id(M5STACK4RELAYSwitch),
        cv.GenerateID(CONF_M5STACK4RELAY_ID): cv.use_id(M5STACK4RELAYComponent),
        cv.Required(CONF_CHANNEL): cv.int_range(min=0, max=3),
    }
)


async def to_code(config):
    paren = await cg.get_variable(config[CONF_M5STACK4RELAY_ID])
    rhs = paren.create_switch(config[CONF_CHANNEL])
    var = cg.Pvariable(config[CONF_ID], rhs)
    await switch.register_switch(var, config)

