# drishti-rt
### SoC 2019 Monte Carlo Path Tracing Renderer

Here is an empty [Cornell Box](https://en.wikipedia.org/wiki/Cornell_box):<br/>
<img src="./images/empty_cornell_box_4spp.png" alt="empty Cornell box" width="550">
<br/> <br/> <br/>
Reflection + Shadows:<br/>
<img src="./images/only_reflection_with_shadows_4spp.png" alt="reflection+shadows" width="550">
<br/> <br/> <br/>
Transmission + Shadows:<br/>
<img src="./images/only_transmission_with_shadows_4spp.png" alt="transmission+shadows" width="550">
<br/> <br/> <br/>
Only ambient lighting:<br/>
<img src="./images/without_shadows_4spp.png" alt="only ambient" width="550">
<br/> <br/> <br/>
Reflection + Transmission + Shadows:<br/>
<img src="./images/without_diffuse_reflection_400spp.png" alt="shadows+reflection+transmission" width="550">
<br/> <br/> <br/>
Without Fresnel (constant reflectance):<br/>
<img src="./images/without_fresnel_400spp.png" alt="constant reflectance (no Fresnel)" width="550">
<br/> <br/> <br/>
With Fresnel reflectance:<br/>
<img src="./images/without_dynamic_sampling_400spp.png" alt="Fresnel reflectance" width="550">
<br/> <br/> <br/>
With dynamic importance sampling added, the final image of this project (400 samples per pixel):<br/>
<img src="./images/final_400spp.png" alt="final 400spp" width="550">
<br/> <br/> <br/>
Same as above, at a much higher sampling rate (20k samples per pixel):<br/>
<img src="./images/final_20000spp.png" alt="final 20000spp" width="550">
