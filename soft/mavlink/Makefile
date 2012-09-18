# Process this file with GNU make
.PHONY: all mavlink_c mavlink_py clean

TOP_DIR = $(shell pwd)
MAVGEN_DIR = ../../../mavlink/pymavlink/generator
FIXED_PY = mavutil.py mavextra.py mavwp.py scanwin32.py

all: mavlink_c mavlink_py

mavlink_c: $(TOP_DIR)/C/protocol.h

mavlink_py: $(TOP_DIR)/python/mavlink.py

$(TOP_DIR)/C/protocol.h: $(TOP_DIR)/definitions/bart.xml
	cd $(MAVGEN_DIR)
	$(MAVGEN_DIR)/mavgen.py --lang=C --wire-protocol=1.0 --output=${TOP_DIR}/C ../../../mavlink/message_definitions/v1.0/common.xml
	
$(TOP_DIR)/python/mavlink.py: $(TOP_DIR)/definitions/bart.xml
	cd $(MAVGEN_DIR)
	$(MAVGEN_DIR)/mavgen.py --lang=python --wire-protocol=1.0 --output=${TOP_DIR}/python ../../../mavlink/message_definitions/v1.0/common.xml

# $(TOP_DIR)/C/protocol.h: $(TOP_DIR)/definitions/bart.xml
# 	cp $(TOP_DIR)/definitions/bart.xml $(MAVGEN_DIR)/message_definitions/v1.0
# 	cd $(MAVGEN_DIR)
# 	$(MAVGEN_DIR)/mavgen.py --lang=C --wire-protocol=1.0 -o C $(MAVGEN_DIR)/message_definitions/v1.0/bart.xml
# 	rm $(MAVGEN_DIR)/message_definitions/v1.0/bart.xml
# 
# 
# $(TOP_DIR)/python/mavlink.py: $(TOP_DIR)/definitions/bart.xml
# 	cp $(TOP_DIR)/definitions/bart.xml $(MAVGEN_DIR)/message_definitions/v1.0
# 	cd $(MAVGEN_DIR)
# 	$(MAVGEN_DIR)/mavgen.py --lang=python --wire-protocol=1.0 -o python/mavlink.py $(MAVGEN_DIR)/message_definitions/v1.0/bart.xml
# 	rm $(MAVGEN_DIR)/message_definitions/v1.0/bart.xml
# 	cd $(MAVGEN_DIR)/../; cp $(FIXED_PY) $(TOP_DIR)/python

clean:
	rm -rf $(TOP_DIR)/python/*.pyc
	rm -rf $(TOP_DIR)/python/*.py
	rm -rf $(TOP_DIR)/C/*
